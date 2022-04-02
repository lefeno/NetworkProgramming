//
// Created by blue on 4/1/22.
//

#include <sys/socket.h>
#include <zconf.h>
#include "client-pseudo/ClientPseudo.hpp"

int main() {
    // my linux can't handle more than 4100 threads
    const int MAX_CLIENT_SPAWN = 100;
    const std::string REMOTE_HOST("127.0.0.1");
    const std::string REMOTE_PORT("8080");
    const int SOCKET_TYPE = SOCK_STREAM;

    for (int i = 0; i < MAX_CLIENT_SPAWN; ++i) {
        network_programming::ClientPseudo(REMOTE_HOST, REMOTE_PORT, SOCKET_TYPE);
    }
    for(;;) {
        ::pause();
    }
    return 0;
}