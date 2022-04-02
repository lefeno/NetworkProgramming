//
// Created by blue on 4/2/22.
//

#include "ServerPosixAsync.hpp"
#include "PosixSyncSession.hpp"
#include <list>
#include <sys/socket.h>
#include <iostream>

namespace network_programming {

    void ServerPosixAsync::handleConnections(const Socket &listenSocket) {
        asyncHandle(listenSocket);
    }

    // FIXME: this is not async yet
    void ServerPosixAsync::asyncHandle(const Socket &listenSocket) {
        fd_set readFds;
        std::list<Socket> connSocketList;
        while(true) {
            FD_ZERO(&readFds);
            FD_SET(listenSocket.getSocketFd(), &readFds);
            auto maxSockFd = listenSocket.getSocketFd();

            for (const auto& connSocket : connSocketList) {
                auto connSocketFd = connSocket.getSocketFd();
                if(connSocketFd) {
                    FD_SET(connSocketFd, &readFds);
                    if (connSocketFd > maxSockFd) {
                        maxSockFd = connSocketFd;
                    }
                }
            }

            //wait for an activity on one of the sockets , timeout is NULL ,
            //so wait indefinitely
            auto activity = select(maxSockFd + 1, &readFds ,NULL ,NULL ,NULL);
            if ((activity < 0) && (EINTR != errno)) {
                printf("select error\n");
            }

            //If something happened on the master socket ,
            //then its an incoming connection
            if (FD_ISSET(listenSocket.getSocketFd(), &readFds)) {
                sockaddr_storage peerAddr{};
                socklen_t peerAddrLen = sizeof(peerAddr);
                auto connSocket = this->accept(listenSocket, reinterpret_cast<sockaddr *>(&peerAddr), peerAddrLen);
                std::cout << "Socket accept at fd " << connSocket.getSocketFd() << std::endl;
                connSocketList.push_back(connSocket);
            }

            //else its some IO operation on some other socket
            auto connSocket = connSocketList.begin();
            while (connSocket != connSocketList.end()) {
                if (FD_ISSET(connSocket->getSocketFd(), &readFds)) {
                    auto dataRecv = connSocket->read();
                    if (dataRecv.length()) {
                        std::cout << "Read from sockFd " << connSocket->getSocketFd() << " bytes " << dataRecv.length()
                                  << " data " << dataRecv << std::endl;

                        auto bytesSent = connSocket->write(dataRecv);
                        std::cout << "Send to sockFd " << connSocket->getSocketFd()
                                  << " bytes " << bytesSent << std::endl;
                    } else {
                        std::cout << "Close socket fd " << connSocket->getSocketFd() << std::endl;
                        connSocket->close();
                        connSocketList.erase(connSocket);
                    }
                    break;
                } else {
                    ++connSocket;
                }
            }
        }
    }
}