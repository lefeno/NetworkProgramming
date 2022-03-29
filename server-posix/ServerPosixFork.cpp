//
// Created by blue on 3/28/22.
//

#include <cerrno>
#include <wait.h>
#include <cstdio>
#include <cstdlib>
#include <zconf.h>
#include <cstring>
#include <iostream>
#include "ServerPosixFork.h"
#include "signal.h"

namespace network_programming {

    static void sigchldHadler(int signal) {
        int saved_errno = errno;
        while(waitpid(-1, nullptr, WNOHANG) > 0);
        errno = saved_errno;
        return;
    }

    void ServerPosixFork::handleConnections(int listenSockFd) {
        registerSig(SIGCHLD, sigchldHadler);
        for (;;) {
            sockaddr_storage peerAddr = {};
            socklen_t peerAddrLen = sizeof(peerAddr);
            auto connectedSockFd = accept(listenSockFd, reinterpret_cast<sockaddr *>(&peerAddr), peerAddrLen);
            std::cout << "Socket accept at fd " << connectedSockFd << std::endl;
            if (connectedSockFd < 0) {
                continue;
            }
            pid_t pid = ::fork();
            if (pid == 0) {
                ::close(listenSockFd);
                handleSingleConnection(connectedSockFd);
                ::close(connectedSockFd);
                exit(0);
            }
            ::close(connectedSockFd);
        }
    }

    void ServerPosixFork::registerSig(int signal, SigFunc sigFunc) {
        struct sigaction sigAction;
        sigAction.sa_handler = sigFunc;
        sigemptyset(&sigAction.sa_mask);
        if (SIGALRM == signal) {
#ifdef	SA_INTERRUPT
            sigAction.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
        } else {
#ifdef	SA_RESTART
            sigAction.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
        }
        if (sigaction(signal, &sigAction, nullptr) < 0) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    }

    void ServerPosixFork::handleSingleConnection(int connectedSockFd) {
        auto bytesSent = ::send(connectedSockFd, SERVER_WELCOME_MSG, strlen(SERVER_WELCOME_MSG), 0);
        std::cout << "Send \"" << SERVER_WELCOME_MSG << "\" to socket fd "
        << connectedSockFd << " bytes sent " << bytesSent << std::endl;

        int bytesRev = 0;
        do {
            char recvBuff[512] = {};
            bytesRev = ::recv(connectedSockFd, recvBuff, sizeof(recvBuff), 0);
            std::cout << "Read from sockFd " << connectedSockFd << " bytes " << bytesRev
            << " data " << std::endl;
            bytesSent = ::send(connectedSockFd, recvBuff, bytesRev, 0);
            std::cout << "Send to sockFd " << connectedSockFd << " bytes " << bytesSent << std::endl;
        } while (bytesRev);
        std::cout << "Close socket fd " << connectedSockFd << std::endl;
    }

    ServerPosixFork::ServerPosixFork() {

    }

    ServerPosixFork::~ServerPosixFork() {

    }
}

