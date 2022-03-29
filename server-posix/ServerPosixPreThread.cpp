//
// Created by blue on 3/29/22.
//

#include <zconf.h>
#include <cstring>
#include <iostream>
#include <client-channel/ClientController.h>
#include "ServerPosixPreThread.h"

#define MAX_THREAD  10

namespace network_programming {

    static void* threadConnHandle(void* arg) {
        ServerPosixPreThread* serverPosixPreThread = (ServerPosixPreThread*) arg;
        serverPosixPreThread->handleSingleConnection();
        return nullptr;
    }

    ServerPosixPreThread::ServerPosixPreThread() {
        this->mutexLock = PTHREAD_MUTEX_INITIALIZER;
        this->threadList.resize(MAX_THREAD, Thread_t());
    }

    ServerPosixPreThread::~ServerPosixPreThread() {

    }

    void ServerPosixPreThread::handleConnections(int listenSockFd) {
        this->listenSockFd = listenSockFd;
        for(auto& threadId : threadList) {
            pthread_create(&threadId.threadTid, NULL, threadConnHandle, this);
        }

        for(;;) {
            pause();
        }
    }

    void ServerPosixPreThread::handleSingleConnection() {
        for(;;) {
            pthread_mutex_lock(&this->mutexLock);
            sockaddr_storage peerAddr{};
            socklen_t peerAddrLen = sizeof(peerAddr);
            auto connectedSockFd = accept(this->listenSockFd, reinterpret_cast<sockaddr *>(&peerAddr), peerAddrLen);
            std::cout << "Accept new connection on sockfd " << connectedSockFd << std::endl;
            pthread_mutex_unlock(&this->mutexLock);
            auto bytesSent = ::send(connectedSockFd, SERVER_WELCOME_MSG, strlen(SERVER_WELCOME_MSG), 0);
            std::cout << "Send \"" << SERVER_WELCOME_MSG << "\" to socket fd "
                      << connectedSockFd << " bytes sent " << bytesSent << std::endl;

            int bytesRev = 0;
            ClientController clientController(connectedSockFd);
            clientChannel.registerObserver(&clientController);
            do {
                char recvBuff[512] = {};
                bytesRev = ::recv(connectedSockFd, recvBuff, sizeof(recvBuff), 0);
                std::cout << "Read from sockFd " << connectedSockFd << " bytes " << bytesRev
                          << " data " << std::endl;
                if (bytesRev > strlen(SEND_ALL_MSG) &&
                    0 == memcmp(recvBuff, SEND_ALL_MSG, strlen(SEND_ALL_MSG))) {
                    memset(recvBuff, 0, sizeof(recvBuff));
                    snprintf(recvBuff, sizeof(recvBuff), SEND_ALL_MSG " from socket fd %d\n", connectedSockFd);
                    this->clientChannel.notifyObserver(recvBuff, strlen(recvBuff));
                } else {
                    auto bytesSent = ::send(connectedSockFd, recvBuff, bytesRev, 0);
                    std::cout << "Send to sockFd " << connectedSockFd << " bytes " << bytesSent << std::endl;
                }
            } while (bytesRev);
            std::cout << "Close socket fd " << connectedSockFd << std::endl;
            clientChannel.removeObserver(&clientController);
            close(connectedSockFd);
        }

    }

}