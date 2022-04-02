//
// Created by blue on 4/2/22.
//

#include <sys/socket.h>
#include <iostream>
#include <thread>
#include "ServerPosixSync.hpp"
#include "PosixSyncSession.hpp"

namespace network_programming {

    void ServerPosixSync::handleConnections(const Socket &listenSocket) {
        for (int i = 0; i < MAX_PRE_THREAD; ++i) {
            std::thread handleConnThread([this] (Room& room, std::mutex& mutex, Socket listenSocket) {
                while (true) {
                    mutex.lock();
                    sockaddr_storage peerAddr{};
                    socklen_t peerAddrLen = sizeof(peerAddr);
                    Socket connSocket = this->accept(listenSocket, &peerAddr, peerAddrLen);
                    mutex.unlock();
                    std::make_shared<PosixSyncSession>(connSocket, room)->start();
                }
                }, std::ref(this->room), std::ref(this->resourceMutex), listenSocket);
            handleConnThread.detach();
        }

        for(;;) {
            pause();
        }
    }

    ServerPosixSync::ServerPosixSync(const std::string &host, const std::string &port, const int &socketType)
            : ServerPosix(host, port, socketType) {

    }

}