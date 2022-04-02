//
// Created by blue on 4/1/22.
//

#include <netinet/in.h>
#include <netdb.h>
#include <system_error>
#include "Connection.hpp"

namespace network_programming {
    Connection::Connection(int socket) : Socket(socket) {

    }

    Connection::Connection(const std::string &remoteAddress, const std::string &service, const int& socketType) {
        addrinfo hints {0};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = socketType;
        hints.ai_flags = AI_PASSIVE;
        addrinfo* pServerInfoList = nullptr;
        auto err = getaddrinfo(remoteAddress.c_str(), service.c_str(), &hints, &pServerInfoList);
        if (err < 0) {
            throw std::system_error(EFAULT, std::generic_category());
        }

        for (addrinfo* pAddr = pServerInfoList; pAddr != nullptr; pAddr = pAddr->ai_next) {
            err = ::connect(this->getSocketFd(), pAddr->ai_addr, pAddr->ai_addrlen);
            if (!err) {
                break;
            }
        }
        freeaddrinfo(pServerInfoList);
        if (err < 0) {
            this->close();
            throw std::system_error(EFAULT, std::generic_category());
        }
    }
}
