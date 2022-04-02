//
// Created by blue on 4/2/22.
//

#ifndef NETWORK_PROGRAMMING_POSIXSESSION_H
#define NETWORK_PROGRAMMING_POSIXSESSION_H

#include "room/Participant.h"
#include "room/Room.hpp"
#include "socket/Socket.hpp"

namespace network_programming {

    class PosixSyncSession: public Participant, public std::enable_shared_from_this<PosixSyncSession> {
    public:
        PosixSyncSession(const Socket& socket, Room& room);
        ~PosixSyncSession() override = default;
        void start();
    private:
        void deliver(const std::string& msg) override ;
        void doRead();
        void doWrite(const std::string& msg);
        Socket socket;
        Room& room;
    };
}

#endif //NETWORKPROGRAMMING_POSIXSESSION_H
