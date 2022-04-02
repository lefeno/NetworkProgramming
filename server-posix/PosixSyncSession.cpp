//
// Created by blue on 4/2/22.
//

#include "PosixSyncSession.hpp"

namespace network_programming {

    PosixSyncSession::PosixSyncSession(const Socket& socket, Room &room): socket(socket), room(room) {
    }

    void PosixSyncSession::start() {
        room.join(shared_from_this());
        doRead();
    }

    void PosixSyncSession::deliver(const std::string& msg) {
        this->socket.write(msg);
    }

    void PosixSyncSession::doRead() {
        std::string data = this->socket.read();
        if (data.empty()) {
            this->socket.close();
            this->room.leave(shared_from_this());
        } else {
            this->room.deliver(data);
        }
    }

    void PosixSyncSession::doWrite(const std::string& msg) {
        this->socket.write(msg);
    }
}