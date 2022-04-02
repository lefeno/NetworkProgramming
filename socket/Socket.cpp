//
// Created by blue on 4/1/22.
//

#include <stdexcept>
#include <sys/socket.h>
#include <zconf.h>
#include <system_error>
#include "Socket.hpp"

namespace network_programming {
    Socket::Socket(int socketFd): connSocketFd(socketFd) {
        if (socketFd < 0) {
            throw std::runtime_error("Socket creation error");
        }
    }

    Socket::Socket(): Socket(::socket(AF_INET, SOCK_STREAM, 0)) {
    }

    std::string Socket::read() const {
        char buffer[MAX_DATA_RECV] = {0};
        auto bytesRecv = ::recv(this->connSocketFd, buffer, sizeof(buffer), 0);
        if (bytesRecv > 0) {
            buffer[bytesRecv] = 0;
            return std::string(buffer, bytesRecv);
        } else if (!bytesRecv) {
            return std::string("");
        } else {
           throw std::system_error(EFAULT, std::generic_category());
        }
    }

    int Socket::getSocketFd() const {
        return this->connSocketFd;
    }

    int Socket::write(const std::string &data) const {
        auto bytesWrite = ::send(this->connSocketFd, data.data(), data.length(), 0);
        if (bytesWrite == data.length()) {
            return bytesWrite;
        } else {
            throw std::system_error(EFAULT, std::generic_category());
        }
    }

    void Socket::close() const {
        ::close(this->connSocketFd);
    }

    void Socket::setOptions(int level, int options) {
        int opt = true;
        auto err = ::setsockopt(this->connSocketFd, level, options, &opt, sizeof(opt));
        if (err < 0) {
            throw std::system_error(EFAULT, std::generic_category());
        }
    }

    bool Socket::operator==(const Socket& socket) const {
        return (this->connSocketFd == socket.getSocketFd());
    }
}
