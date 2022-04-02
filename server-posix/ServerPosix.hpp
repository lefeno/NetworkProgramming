//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIX_H
#define NETWORK_PROGRAMMING_SERVERPOSIX_H

#include <string>
#include "socket/Socket.hpp"
#include "room/Room.hpp"

namespace network_programming {
    class ServerPosix {
    public:
        ServerPosix(const std::string& host, const std::string& port, const int &socketType);
        ~ServerPosix();
        void run();
    protected:
        void listen(const Socket& listenSocket);
        Socket accept(const Socket& listenSocket, void* peerAddr, uint32_t &peerAddrLen);
        virtual void handleConnections(const Socket& listenSocket) = 0;
        static void printServerInfo(int ai_family, void* pSockAddr);

        enum {MAX_LISTEN_QUEUE = 20};
        Socket serverSocket;
        Room room;
    };
}

#endif //NETWORK_PROGRAMMING_SERVERPOSIX_H
