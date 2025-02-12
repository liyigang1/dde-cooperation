// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef WORKSPACEWIDGET_H
#define WORKSPACEWIDGET_H

#include "global_defines.h"
#include "info/deviceinfo.h"

#include <QWidget>
#include <QScopedPointer>

namespace cooperation_core {

class WorkspaceWidgetPrivate;
class WorkspaceWidget : public QWidget
{
    Q_OBJECT
public:
    enum PageName {
        kLookignForDeviceWidget = 0,
        kNoNetworkWidget,
        kNoResultWidget,
        kDeviceListWidget,

        kUnknownPage = 99,
    };

    explicit WorkspaceWidget(QWidget *parent = nullptr);

    int itemCount();
    void switchWidget(PageName page);
    void addDeviceInfos(const QList<DeviceInfoPointer> &infoList);
    void removeDeviceInfos(const QString &ip);
    void addDeviceOperation(const QVariantMap &map);
    DeviceInfoPointer findDeviceInfo(const QString &ip);

    void clear();

protected:
    bool event(QEvent *event) override;

private:
    QScopedPointer<WorkspaceWidgetPrivate> d;
};

}   // namespace cooperation_core

#endif   // WORKSPACEWIDGET_H
