//
// Created by blue on 4/2/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIXASYNC_HPP
#define NETWORK_PROGRAMMING_SERVERPOSIXASYNC_HPP

#include "ServerPosix.hpp"

namespace network_programming {

    class ServerPosixAsync: public ServerPosix {
    public:
        void handleConnections(const Socket &listenSocket) override;
    private:
        [[noreturn]] void asyncHandle(const Socket& listenSocket);
    };
}


#endif //NETWORK_PROGRAMMING_SERVERPOSIXASYNC_HPP
