//
// Created by blue on 4/2/22.
//

#ifndef NETWORK_PROGRAMMING_POSIXSESSION_H
#define NETWORK_PROGRAMMING_POSIXSESSION_H

#include "room/Participant.h"
#include "room/Room.hpp"
#include "socket/Socket.hpp"

namespace network_programming {

    class PosixSession: public Participant {
    public:
        PosixSession(Socket socket, Room& room);
        ~PosixSession();
        void start();
    private:

        Socket socket;
        Room& room;
    };
}

#endif //NETWORKPROGRAMMING_POSIXSESSION_H
