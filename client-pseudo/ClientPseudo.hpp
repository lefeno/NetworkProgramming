//
// Created by blue on 4/1/22.
//

#ifndef NETWORK_PROGRAMMING_CLIENTPSEUDO_H
#define NETWORK_PROGRAMMING_CLIENTPSEUDO_H

#include "socket/Connection.hpp"

namespace network_programming {

    class ClientPseudo {
    public:
        ClientPseudo(const std::string& remoteHost, const std::string& port, const int& socketType);
    };
};

#endif //NETWORKPROGRAMMING_CLIENTPSEUDO_H
