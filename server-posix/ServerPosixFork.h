//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIXFORK_H
#define NETWORK_PROGRAMMING_SERVERPOSIXFORK_H

#include "client-channel/ClientChannel.h"
#include "ServerPosix.hpp"

typedef void (*SigFunc) (int) ;

namespace network_programming {
    class ServerPosixFork : public ServerPosix {
    public:
        ServerPosixFork();
        ~ServerPosixFork();
    protected:
        virtual void handleConnections(int listenSockFd) override;
        void registerSig(int signal, SigFunc sigFunc);
        virtual void handleSingleConnection(int connectedSockFd);
    };
}

#endif //NETWORK_PROGRAMMING_SERVERPOSIXFORK_H
