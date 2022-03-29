//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIXPREFORK_H
#define NETWORK_PROGRAMMING_SERVERPOSIXPREFORK_H

#include <vector>
#include "server-posix/ServerPosixFork.h"

namespace network_programming {
    class ServerPosixPreFork: public ServerPosixFork {
    public:
        ServerPosixPreFork();
        ~ServerPosixPreFork();
    protected:
        void handleConnections(int listenSockFd) override;
        pid_t forkChild(int listenSockFd);
        int processChild(int listenSockFd);
        long* createMeter(int childNum);
        void createLock(const char* pathName);
        void lockWait();
        void lockRelease();
    private:
        pthread_mutex_t *pProcessMutex;
    };
}

#endif //NETWORK_PROGRAMMING_SERVERPOSIXPREFORK_H
