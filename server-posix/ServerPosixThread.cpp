//
// Created by blue on 3/29/22.
//

#include <zconf.h>
#include <iostream>
#include <cstring>
#include "ServerPosixThread.h"
#include "client-channel/ClientController.h"

namespace network_programming {

    static void* handleConnThread(void* arg) {
        pthread_detach(pthread_self());
        ServerPosixThread* serverPosixThread = (ServerPosixThread*) arg;
        serverPosixThread->handleThreadConn();
        return nullptr;
    }

    ServerPosixThread::ServerPosixThread() {

    }

    ServerPosixThread::~ServerPosixThread() {

    }

    void ServerPosixThread::handleThreadConn() {
        handleSingleConnection(this->currConnFd);
        close(this->currConnFd);
    }

    void ServerPosixThread::handleConnections(int listenSockFd) {
        for (;;) {
            sockaddr_storage peerAddr{};
            socklen_t peerAddrLen = sizeof(peerAddr);
            this->currConnFd = accept(listenSockFd, reinterpret_cast<sockaddr *>(&peerAddr), peerAddrLen);
            std::cout << "Accept new connection on sockfd " << this->currConnFd << std::endl;
            pthread_t tid;
            pthread_create(&tid, NULL, handleConnThread, this);
        }
    }

    void ServerPosixThread::handleSingleConnection(int connectedSockFd) {
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
    }
}