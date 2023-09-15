// Autogenerated.
// DO NOT EDIT. All changes will be undone.
#pragma once

#include "co/rpc.h"

namespace ipc {

class Common : public rpc::Service {
  public:
    typedef std::function<void(co::Json&, co::Json&)> Fun;

    Common() {
        using std::placeholders::_1;
        using std::placeholders::_2;
        _methods["Common.compatible"] = std::bind(&Common::compatible, this, _1, _2);
        _methods["Common.syncConfig"] = std::bind(&Common::syncConfig, this, _1, _2);
        _methods["Common.syncPeers"] = std::bind(&Common::syncPeers, this, _1, _2);
        _methods["Common.tryConnect"] = std::bind(&Common::tryConnect, this, _1, _2);
        _methods["Common.tryTargetSpace"] = std::bind(&Common::tryTargetSpace, this, _1, _2);
        _methods["Common.tryApplist"] = std::bind(&Common::tryApplist, this, _1, _2);
        _methods["Common.chatMessage"] = std::bind(&Common::chatMessage, this, _1, _2);
        _methods["Common.miscMessage"] = std::bind(&Common::miscMessage, this, _1, _2);
        _methods["Common.commNotify"] = std::bind(&Common::commNotify, this, _1, _2);
    }

    virtual ~Common() {}

    virtual const char* name() const {
        return "Common";
    }

    virtual const co::map<const char*, Fun>& methods() const {
        return _methods;
    }

    virtual void compatible(co::Json& req, co::Json& res) = 0;

    virtual void syncConfig(co::Json& req, co::Json& res) = 0;

    virtual void syncPeers(co::Json& req, co::Json& res) = 0;

    virtual void tryConnect(co::Json& req, co::Json& res) = 0;

    virtual void tryTargetSpace(co::Json& req, co::Json& res) = 0;

    virtual void tryApplist(co::Json& req, co::Json& res) = 0;

    virtual void chatMessage(co::Json& req, co::Json& res) = 0;

    virtual void miscMessage(co::Json& req, co::Json& res) = 0;

    virtual void commNotify(co::Json& req, co::Json& res) = 0;

  private:
    co::map<const char*, Fun> _methods;
};

struct Config {
    struct _unamed_s1 {
        fastring name;
        fastring value;

        void from_json(const co::Json& _x_) {
            name = _x_.get("name").as_c_str();
            value = _x_.get("value").as_c_str();
        }

        co::Json as_json() const {
            co::Json _x_;
            _x_.add_member("name", name);
            _x_.add_member("value", value);
            return _x_;
        }
    };

    co::vector<_unamed_s1> ao;

    void from_json(const co::Json& _x_) {
        do {
            auto& _unamed_v1 = _x_.get("ao");
            for (uint32 i = 0; i < _unamed_v1.array_size(); ++i) {
                _unamed_s1 _unamed_v2;
                _unamed_v2.from_json(_unamed_v1[i]);
                ao.emplace_back(std::move(_unamed_v2));
            }
        } while (0);
    }

    co::Json as_json() const {
        co::Json _x_;
        do {
            co::Json _unamed_v1;
            for (size_t i = 0; i < ao.size(); ++i) {
                _unamed_v1.push_back(ao[i].as_json());
            }
            _x_.add_member("ao", _unamed_v1);
        } while (0);
        return _x_;
    }
};

struct PeerInfo {
    fastring uuid;
    fastring ipv4;
    fastring username;
    fastring hostname;
    int32 device_os;
    fastring proto_version;
    bool mode;

    void from_json(const co::Json& _x_) {
        uuid = _x_.get("uuid").as_c_str();
        ipv4 = _x_.get("ipv4").as_c_str();
        username = _x_.get("username").as_c_str();
        hostname = _x_.get("hostname").as_c_str();
        device_os = (int32)_x_.get("device_os").as_int64();
        proto_version = _x_.get("proto_version").as_c_str();
        mode = _x_.get("mode").as_bool();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("uuid", uuid);
        _x_.add_member("ipv4", ipv4);
        _x_.add_member("username", username);
        _x_.add_member("hostname", hostname);
        _x_.add_member("device_os", device_os);
        _x_.add_member("proto_version", proto_version);
        _x_.add_member("mode", mode);
        return _x_;
    }
};

struct PeerList {
    int32 code;
    co::vector<PeerInfo> peers;

    void from_json(const co::Json& _x_) {
        code = (int32)_x_.get("code").as_int64();
        do {
            auto& _unamed_v1 = _x_.get("peers");
            for (uint32 i = 0; i < _unamed_v1.array_size(); ++i) {
                PeerInfo _unamed_v2;
                _unamed_v2.from_json(_unamed_v1[i]);
                peers.emplace_back(std::move(_unamed_v2));
            }
        } while (0);
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("code", code);
        do {
            co::Json _unamed_v1;
            for (size_t i = 0; i < peers.size(); ++i) {
                _unamed_v1.push_back(peers[i].as_json());
            }
            _x_.add_member("peers", _unamed_v1);
        } while (0);
        return _x_;
    }
};

struct ConnTarget {
    fastring ipv4;
    uint32 port;
    fastring authkey;

    void from_json(const co::Json& _x_) {
        ipv4 = _x_.get("ipv4").as_c_str();
        port = (uint32)_x_.get("port").as_int64();
        authkey = _x_.get("authkey").as_c_str();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("ipv4", ipv4);
        _x_.add_member("port", port);
        _x_.add_member("authkey", authkey);
        return _x_;
    }
};

struct ConnResult {
    int32 code;
    fastring reason;

    void from_json(const co::Json& _x_) {
        code = (int32)_x_.get("code").as_int64();
        reason = _x_.get("reason").as_c_str();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("code", code);
        _x_.add_member("reason", reason);
        return _x_;
    }
};

struct SpaceSize {
    fastring dir;
    uint64 size;

    void from_json(const co::Json& _x_) {
        dir = _x_.get("dir").as_c_str();
        size = (uint64)_x_.get("size").as_int64();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("dir", dir);
        _x_.add_member("size", size);
        return _x_;
    }
};

struct AppList {
    fastring displayname;
    int32 run_type;
    fastring pkgname;
    fastring version;
    fastring vonder;

    void from_json(const co::Json& _x_) {
        displayname = _x_.get("displayname").as_c_str();
        run_type = (int32)_x_.get("run_type").as_int64();
        pkgname = _x_.get("pkgname").as_c_str();
        version = _x_.get("version").as_c_str();
        vonder = _x_.get("vonder").as_c_str();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("displayname", displayname);
        _x_.add_member("run_type", run_type);
        _x_.add_member("pkgname", pkgname);
        _x_.add_member("version", version);
        _x_.add_member("vonder", vonder);
        return _x_;
    }
};

struct Chat {
    fastring username;
    fastring text;

    void from_json(const co::Json& _x_) {
        username = _x_.get("username").as_c_str();
        text = _x_.get("text").as_c_str();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("username", username);
        _x_.add_member("text", text);
        return _x_;
    }
};

struct NotifyComm {
    int32 id;
    int32 type;
    int32 result;
    fastring content;

    void from_json(const co::Json& _x_) {
        id = (int32)_x_.get("id").as_int64();
        type = (int32)_x_.get("type").as_int64();
        result = (int32)_x_.get("result").as_int64();
        content = _x_.get("content").as_c_str();
    }

    co::Json as_json() const {
        co::Json _x_;
        _x_.add_member("id", id);
        _x_.add_member("type", type);
        _x_.add_member("result", result);
        _x_.add_member("content", content);
        return _x_;
    }
};

} // ipc
