//
// Created by blue on 3/28/22.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <zconf.h>
#include "ServerPosix.h"

#define HTTP_PORT "8080"
#define MAX_LISTEN_QUEUE    20
#define MAX_CLIENT_CONNECTED   10

namespace network_programming {
    ServerPosix::ServerPosix() {

    }

    ServerPosix::~ServerPosix() {

    }

    int ServerPosix::createSocket(const char* host, const char* service, const int &socketType) {
        addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = socketType;
        hints.ai_flags = AI_PASSIVE;
        addrinfo* pServerInfoList = nullptr;
        ::getaddrinfo(host, service, &hints, &pServerInfoList);

        for (addrinfo* pAddr = pServerInfoList; pAddr != nullptr; pAddr = pAddr->ai_next) {
            auto serverSocketFd = ::socket(pAddr->ai_family, pAddr->ai_socktype, pAddr->ai_protocol);
            if (serverSocketFd < 0) {
                perror("socket");
                continue;
            }

            int opt = true;
            auto err = ::setsockopt(serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            if (err) {
                perror("setsockopt");
                continue;
            }

            err = ::bind(serverSocketFd, pAddr->ai_addr, pAddr->ai_addrlen);
            if (err) {
                perror("bind");
                continue;
            } else {
                printServerInfo(pAddr->ai_family, pAddr->ai_addr);
                ::freeaddrinfo(pServerInfoList);
                return serverSocketFd;
            }
        }
        exit(EXIT_FAILURE);
        return -1;
    }

    int ServerPosix::listen(int listenSockFd) {
        char* pBacklogEnvValue = getenv("LISTENQ");
        int backlogValue = 0;
        if (pBacklogEnvValue) {
            backlogValue = atoi(pBacklogEnvValue);
        } else {
            backlogValue = MAX_LISTEN_QUEUE;
        }
        auto err = ::listen(listenSockFd, backlogValue);
        if (err) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        return 0;
    }

    void ServerPosix::run() {
        int listenSocketFd = createSocket(nullptr, HTTP_PORT, SOCK_STREAM);
        std::cout << "Create listenSocketFd " << listenSocketFd << std::endl;
        listen(listenSocketFd);
        handleConnections(listenSocketFd);
    }

    void ServerPosix::printServerInfo(int ai_family, void *pSockAddr) {
        void* pAddrPos = nullptr;
        uint16_t port = 0;
        switch (ai_family) {
            case AF_INET: {
                sockaddr_in* ipv4 = static_cast<sockaddr_in *>(pSockAddr);
                pAddrPos = &ipv4->sin_addr;
                port = ipv4->sin_port;
                break;
            }
            case AF_INET6: {
                sockaddr_in6* ipv6 = static_cast<sockaddr_in6 *>(pSockAddr);
                pAddrPos = &ipv6->sin6_addr;
                port = ipv6->sin6_port;
                break;
            }
            default: {
                std::cout << "Undefined address family" << std::endl;
                return;
            }
        }
        char addrBuffer[INET6_ADDRSTRLEN] = {};
        std::cout << "Server socket [" << inet_ntop(ai_family, pAddrPos, addrBuffer, INET6_ADDRSTRLEN) << "]:" << ntohs(port) << std::endl;
    }

    void ServerPosix::handleConnections(int listenSockFd) {
        fd_set readFds;
        std::list<int> clientConnFds;
        while(true) {
            FD_ZERO(&readFds);
            FD_SET(listenSockFd, &readFds);
            auto maxSockFd = listenSockFd;

            for (const auto& clientFd : clientConnFds) {
                if(clientFd) {
                    FD_SET(clientFd , &readFds);
                    if (clientFd > maxSockFd) {
                        maxSockFd = clientFd;
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
            if (FD_ISSET(listenSockFd, &readFds)) {
                sockaddr_storage peerAddr{};
                socklen_t peerAddrLen = sizeof(peerAddr);
                auto connectedSockFd = accept(listenSockFd, reinterpret_cast<sockaddr *>(&peerAddr), peerAddrLen);
                if (connectedSockFd < 0) {
                    continue;
                }
                std::cout << "Socket accept at fd " << connectedSockFd << std::endl;
                clientConnFds.push_back(connectedSockFd);
                auto bytesSent = ::send(connectedSockFd, SERVER_WELCOME_MSG, strlen(SERVER_WELCOME_MSG), 0);
                std::cout << "Send \"" << SERVER_WELCOME_MSG << "\" to socket fd "
                          << connectedSockFd << " bytes sent " << bytesSent << std::endl;
            }

            //else its some IO operation on some other socket
            for (auto const& currConnFd : clientConnFds) {
                if (FD_ISSET(currConnFd, &readFds)) {
                    char recvBuff[512] = {};
                    auto bytesRev = ::recv(currConnFd, recvBuff, sizeof(recvBuff), 0);
                    if (bytesRev) {
                        std::cout << "Read from sockFd " << currConnFd << " bytes " << bytesRev
                                  << " data " << recvBuff << std::endl;
                        if (bytesRev > strlen(SEND_ALL_MSG) &&
                        0 == memcmp(recvBuff, SEND_ALL_MSG, strlen(SEND_ALL_MSG))) {
                            for (const auto& clientFd : clientConnFds) {
                                memset(recvBuff, 0, sizeof(recvBuff));
                                snprintf(recvBuff, sizeof(recvBuff), SEND_ALL_MSG " from socket fd %d\n", currConnFd);
                                auto bytesSent = ::send(clientFd, recvBuff, strlen(recvBuff), 0);
                                std::cout << "Send to sockFd " << clientFd << " bytes " << bytesSent << std::endl;
                            }
                        } else {
                            auto bytesSent = ::send(currConnFd, recvBuff, bytesRev, 0);
                            std::cout << "Send to sockFd " << currConnFd << " bytes " << bytesSent << std::endl;
                        }
                    } else {
                        std::cout << "Close socket fd " << currConnFd << std::endl;
                        ::close(currConnFd);
                        clientConnFds.remove(currConnFd);
                    }
                }
            }
        }
    }

    int ServerPosix::accept(int lisenSockFd, void *peerAddr, uint32_t &peerAddrLen) {
        int connSockFd = -1;
        do {
            connSockFd = ::accept(lisenSockFd, static_cast<sockaddr *>(peerAddr), &peerAddrLen);
        } while (connSockFd < 0 && (EINTR == errno || ECONNABORTED == errno));
        if (connSockFd < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        } else {
            return connSockFd;
        }
    }

}