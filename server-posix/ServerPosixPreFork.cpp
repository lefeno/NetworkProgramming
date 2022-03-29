//
// Created by blue on 3/28/22.
//

#include "ServerPosixPreFork.h"
#include <vector>
#include <zconf.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>

#define MAX_CHILD_FORK 10

static std::vector<pid_t> pidList(MAX_CHILD_FORK, 0);

namespace network_programming {
    static void sigintHandler(int signal) {
        for (auto& pid : pidList) {
            kill(pid, SIGTERM);
        }
        while (wait(nullptr) > 0);
        if (ECHILD == errno) {
            perror("wait error");
        }
        exit(0);
    }

    void ServerPosixPreFork::handleConnections(int listenSockFd) {
        createLock("/dev/zero");
        for (auto& pid : pidList) {
            pid = forkChild(listenSockFd);
        }
        registerSig(SIGINT, sigintHandler);

        for(;;) {
            pause();
        }
    }

    pid_t ServerPosixPreFork::forkChild(int listenSockFd) {
        pid_t pid = fork();
        if (pid) {
            return pid;
        }
        return processChild(listenSockFd);
    }

    int ServerPosixPreFork::processChild(int listenSockFd) {
        for (;;) {
            sockaddr_storage peerAddr = {};
            socklen_t peerAddrLen = sizeof(peerAddr);
            lockWait();
            printf("Wait accept on process %d\n", getpid());
            auto connectedSockFd = accept(listenSockFd, reinterpret_cast<sockaddr *>(&peerAddr), peerAddrLen);
            lockRelease();
            if (connectedSockFd < 0) {
                continue;
            }
            std::cout << "Socket accept at fd " << connectedSockFd << std::endl;
            handleSingleConnection(connectedSockFd);
            ::close(connectedSockFd);
        }
    }

    long *ServerPosixPreFork::createMeter(int childNum) {
#ifdef MAP_ANON
        void *ptr = (mmap(0, childNum * sizeof(long), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1,
                          0));
#else
        fd = open("/dev/zero", O_RDWR, 0);
        ptr = mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
                      MAP_SHARED, fd, 0);
        close(fd);
#endif
        return static_cast<long *>(ptr);
    }

    ServerPosixPreFork::ServerPosixPreFork() {

    }

    ServerPosixPreFork::~ServerPosixPreFork() {

    }

    void ServerPosixPreFork::createLock(const char* pathName) {
        int fd = open(pathName, O_RDWR, 0);
        if (fd < 0) {
            perror("createLock open");
            exit(EXIT_FAILURE);
        }
        this->pProcessMutex = static_cast<pthread_mutex_t *>(mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE,
                                                            MAP_SHARED, fd, 0));
        close(fd);
        pthread_mutexattr_t mutexAttr;
        pthread_mutexattr_init(&mutexAttr);
        pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(this->pProcessMutex, &mutexAttr);
    }

    void ServerPosixPreFork::lockWait() {
        pthread_mutex_lock(this->pProcessMutex);
    }

    void ServerPosixPreFork::lockRelease() {
        pthread_mutex_unlock(this->pProcessMutex);
    }
}
