#include "InputGrabberWrapper.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QProcess>

#include "config.h"
#include "Manager.h"
#include "Machine/Machine.h"
#include "utils/message_helper.h"
#include "protocol/ipc_message.pb.h"

InputGrabberWrapper::InputGrabberWrapper(Manager *manager, const std::filesystem::path &path)
    : m_manager(manager)
    , m_server(new QLocalServer(this))
    , m_conn(nullptr)
    , m_process(new QProcess(this))
    , m_path(QString::fromStdString(path)) {
    auto name = QString("DDECooperationInputEmitter-%1").arg(QString(m_path).replace("/", "_"));
    m_server->listen(name);
    m_server->setMaxPendingConnections(1);
    qDebug() << "InputGrabber listen addr:" << m_server->serverName();

    connect(m_server,
            &QLocalServer::newConnection,
            this,
            &InputGrabberWrapper::handleNewConnection);

    connect(m_process,
            static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this,
            &InputGrabberWrapper::onProcessClosed);
    m_process->start(INPUT_GRABBER_PATH,
                     QStringList{m_server->serverName(), QString::fromStdString(path.string())});
}

InputGrabberWrapper::~InputGrabberWrapper() {
    m_server->close();
    if (m_conn) {
        m_conn->close();
    }
    m_process->kill();
}

void InputGrabberWrapper::setMachine(const std::weak_ptr<Machine> &machine) {
    m_machine = machine;
}

void InputGrabberWrapper::start() {
    qDebug() << "start" << m_path;
    InputGrabberParent msg;
    msg.mutable_start();
    m_conn->write(MessageHelper::genMessage(msg));
}

void InputGrabberWrapper::stop() {
    qDebug() << "stop" << m_path;
    InputGrabberParent msg;
    msg.mutable_stop();
    m_conn->write(MessageHelper::genMessage(msg));
}

void InputGrabberWrapper::handleNewConnection() {
    if (m_conn) {
        return;
    }

    qDebug() << "InputGrabber new connection" << m_path;
    m_conn = m_server->nextPendingConnection();
    m_server->close();

    connect(m_conn, &QLocalSocket::readyRead, this, &InputGrabberWrapper::onReceived);
    connect(m_conn, &QLocalSocket::disconnected, this, &InputGrabberWrapper::onDisconnected);
}

void InputGrabberWrapper::onProcessClosed([[maybe_unused]] int exitCode,
                                          [[maybe_unused]] QProcess::ExitStatus exitStatus) {
    qDebug() << "onProcessClosed" << m_path;
    m_manager->removeInputGrabber(m_path.toStdString());
}

void InputGrabberWrapper::onReceived() {
    qDebug() << "input-grabber onReceived";

    while (m_conn->size() >= header_size) {
        QByteArray buffer = m_conn->peek(header_size);
        auto header = MessageHelper::parseMessageHeader(buffer);
        if (!header.legal()) {
            qWarning() << "illegal message from input-grabber";
            return;
        }

        if (m_conn->size() < static_cast<qint64>(header_size + header.size())) {
            qDebug() << "partial content";
            return;
        }

        m_conn->read(header_size);
        auto size = header.size();
        buffer = m_conn->read(size);

        InputGrabberChild base = MessageHelper::parseMessageBody<InputGrabberChild>(buffer.data(),
                                                                                    buffer.size());

        switch (base.payload_case()) {
        case InputGrabberChild::PayloadCase::kDeviceType: {
            m_type = base.devicetype();
            break;
        }
        case InputGrabberChild::PayloadCase::kInputEvent: {
            auto machine = m_machine.lock();
            if (machine) {
                auto inputEvent = base.inputevent();
                machine->onInputGrabberEvent(m_type,
                                             inputEvent.type(),
                                             inputEvent.code(),
                                             inputEvent.value());
            }
            break;
        }
        case InputGrabberChild::PAYLOAD_NOT_SET: {
            break;
        }
        }
    }
}

void InputGrabberWrapper::onDisconnected() {
    m_process->kill();
}
