//
// Created by blue on 4/1/22.
//

#ifndef NETWORK_PROGRAMMING_SOCKET_H
#define NETWORK_PROGRAMMING_SOCKET_H

#include <string>

namespace network_programming {
    class Socket {
    public:
        explicit Socket(int socketFd);
        Socket();
        ~Socket() = default;
        std::string read() const;
        int write(const std::string& data) const;
        int getSocketFd() const;
        void close() const;
        void setOptions(int level, int options);
        bool operator==(const Socket& socket) const;
    private:
        enum {MAX_DATA_RECV = 1024};
        int connSocketFd;
    };
}

#endif //NETWORKPROGRAMMING_SOCKET_H
