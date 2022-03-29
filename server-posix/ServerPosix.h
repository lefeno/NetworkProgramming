//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIX_H
#define NETWORK_PROGRAMMING_SERVERPOSIX_H

#include <netdb.h>
#include <client-channel/ClientChannel.h>
#include <string>

#define SERVER_WELCOME_MSG  "Welcome to my server"
#define SEND_ALL_MSG        "All"

namespace network_programming {
    class ServerPosix {
    public:
        ServerPosix();
        ~ServerPosix();
        void run();
    protected:
        int createSocket(const char* host, const char* service, const int& socketType);
        int listen(int listenSockFd);
        int accept(int lisenSockFd, void* peerAddr, uint32_t &peerAddrLen);
        virtual void handleConnections(int listenSockFd);
        void printServerInfo(int ai_family, void* pSockAddr);
    };
}

#endif //NETWORK_PROGRAMMING_SERVERPOSIX_H
