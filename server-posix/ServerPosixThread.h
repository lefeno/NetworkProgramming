//
// Created by blue on 3/29/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIXTHREAD_H
#define NETWORK_PROGRAMMING_SERVERPOSIXTHREAD_H

#include "ServerPosixFork.h"
#include "client-channel/ClientChannel.h"

namespace network_programming {
    class ServerPosixThread: public ServerPosixFork {
    public:
        ServerPosixThread();
        ~ServerPosixThread();
        void handleThreadConn();
    private:
        void handleConnections(int listenSockFd) override;
        void handleSingleConnection(int connectedSockFd) override;
        int currConnFd;
        ClientChannel clientChannel;
    };
}

#endif //NETWORK_PROGRAMMING_SERVERPOSIXTHREAD_H
