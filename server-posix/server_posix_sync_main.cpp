//
// Created by blue on 4/2/22.
//

#include <iostream>
#include <sys/socket.h>
#include "server-posix/ServerPosixSync.hpp"

int main() {
    try {
        const std::string REMOTE_HOST("");
        const std::string REMOTE_PORT("8080");
        const int SOCKET_TYPE = SOCK_STREAM;
        network_programming::ServerPosixSync serverPosix(REMOTE_HOST, REMOTE_PORT, SOCKET_TYPE);
        serverPosix.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}