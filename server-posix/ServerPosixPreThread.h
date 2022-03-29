//
// Created by blue on 3/29/22.
//

#ifndef NETWORKPROGRAMMING_SERVERPOSIXPRETHREAD_H
#define NETWORKPROGRAMMING_SERVERPOSIXPRETHREAD_H

#include <vector>
#include "ServerPosix.h"

namespace network_programming {
    struct Thread_t {
        pthread_t threadTid;
        long threadCount;
    };

    class ServerPosixPreThread: public ServerPosix {
    public:
        ServerPosixPreThread();
        ~ServerPosixPreThread();
        void handleSingleConnection();
    protected:
        void handleConnections(int listenSockFd) override;
    private:
        pthread_mutex_t mutexLock;
        std::vector<Thread_t> threadList;
        int listenSockFd;
        ClientChannel clientChannel;
    };
}

#endif //NETWORKPROGRAMMING_SERVERPOSIXPRETHREAD_H
