//
// Created by blue on 3/28/22.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include "ServerPosix.hpp"
#include <list>
#include <netdb.h>
#include "PosixSyncSession.hpp"

namespace network_programming {
    ServerPosix::ServerPosix(const std::string& host, const std::string& port, const int &socketType) {
        addrinfo hints {0};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = socketType;
        hints.ai_flags = AI_PASSIVE;
        addrinfo* pServerInfoList = nullptr;
        const char* hostAddr = host.empty() ? nullptr : host.c_str();
        auto err = getaddrinfo(hostAddr, port.c_str(), &hints, &pServerInfoList);
        if (err < 0) {
            throw std::system_error(EFAULT, std::generic_category());
        }

        for (addrinfo* pAddr = pServerInfoList; pAddr != nullptr; pAddr = pAddr->ai_next) {
            this->serverSocket = Socket(::socket(pAddr->ai_family, pAddr->ai_socktype, pAddr->ai_protocol));
            this->serverSocket.setOptions(SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT);
            err = ::bind(this->serverSocket.getSocketFd(), pAddr->ai_addr, pAddr->ai_addrlen);
            if (err) {
                perror("bind");
                continue;
            } else {
                printServerInfo(pAddr->ai_family, pAddr->ai_addr);
                ::freeaddrinfo(pServerInfoList);
                return;
            }
        }
        freeaddrinfo(pServerInfoList);
        throw std::system_error(EFAULT, std::generic_category());
    }

    ServerPosix::~ServerPosix() {

    }

    void ServerPosix::listen(const Socket& listenSocket) {
        char* pBacklogEnvValue = getenv("LISTENQ");
        int backlogValue = 0;
        if (pBacklogEnvValue) {
            backlogValue = atoi(pBacklogEnvValue);
        } else {
            backlogValue = MAX_LISTEN_QUEUE;
        }
        auto err = ::listen(listenSocket.getSocketFd(), backlogValue);
        if (err) {
            throw std::system_error(EFAULT, std::generic_category());
        }
    }

    void ServerPosix::run() {
        std::cout << "Create listenSocketFd " << this->serverSocket.getSocketFd() << std::endl;
        listen(this->serverSocket);
        handleConnections(this->serverSocket);
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

    Socket ServerPosix::accept(const Socket& listenSocket, void *peerAddr, uint32_t &peerAddrLen) {
        int connSockFd = -1;
        do {
            connSockFd = ::accept(listenSocket.getSocketFd(), static_cast<sockaddr *>(peerAddr), &peerAddrLen);
        } while (connSockFd < 0 && (EINTR == errno || ECONNABORTED == errno));
        if (connSockFd < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        } else {
            return Socket(connSockFd);
        }
    }

}