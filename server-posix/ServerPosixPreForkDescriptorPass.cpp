//
// Created by blue on 3/28/22.
//

#include <zconf.h>
#include "ServerPosixPreForkDescriptorPass.h"

#define MAX_CHILD_FORK 10

namespace network_programming {

    ServerPosixPreForkDescriptorPass::ServerPosixPreForkDescriptorPass() {

    }

    ServerPosixPreForkDescriptorPass::~ServerPosixPreForkDescriptorPass() {

    }

    void ServerPosixPreForkDescriptorPass::handleConnections(int listenSockFd) {
        fd_set socketSet;
        FD_ZERO(&socketSet);
        FD_SET(listenSockFd, &socketSet);

        auto maxFd = listenSockFd;
        this->pChildTracker.resize(MAX_CHILD_FORK);
        for (int i = 0; i < MAX_CHILD_FORK; ++i) {
            pChildTracker.push_back(forkChild(listenSockFd));
            FD_SET(pChildTracker[i].childPipeFd, &socketSet);
        }
    }

    ChildTrack_t ServerPosixPreForkDescriptorPass::forkChild(int listenSockFd) {
        int sockPipeFd[2];
        auto err = socketpair(AF_LOCAL, SOCK_STREAM, 0, sockPipeFd);
        if (err) {
            perror("socketpair");
            exit(EXIT_FAILURE);
        }
        pid_t pid = fork();
        if (pid) {
            close(sockPipeFd[1]);
            ChildTrack_t childTrack{};
            childTrack.childPid = pid;
            childTrack.childPipeFd = sockPipeFd[0];
            childTrack.childStatus = 0;
            return childTrack;
        }
        dup2(sockPipeFd[1], STDERR_FILENO);
        close(sockPipeFd[0]);
        close(sockPipeFd[1]);
        close(listenSockFd);
        processChild();
        exit(0);
    }

    int ServerPosixPreForkDescriptorPass::processChild() {
        for (;;) {
            char c;
            int connFd;
//            auto bytesRead = read_fd(STDERR_FILENO, &c, sizeof(c), &connFd);
        }
        return 0;
    }
}