//
// Created by blue on 4/1/22.
//

#ifndef NETWORK_PROGRAMMING_CONNECTION_H
#define NETWORK_PROGRAMMING_CONNECTION_H

#include "Socket.hpp"

namespace network_programming {

    class Connection: public Socket {
    public:
        explicit Connection(int socket);
        Connection(const std::string& remoteAddress, const std::string& port, const int& socketType);
    };
};


#endif //NETWORK_PROGRAMMING_CONNECTION_H
