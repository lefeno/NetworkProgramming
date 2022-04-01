#include <iostream>
#include "server-posix/ServerPosixFork.h"
#include "server-posix/ServerPosixPreFork.h"
#include "server-posix/ServerPosixThread.h"
#include "server-posix/ServerPosixPreThread.h"
#include "server-asio/ServerAsio.hpp"

using namespace std;
using namespace network_programming;

#define SERVER_PORT  8080

int main() {
    boost::asio::io_context ioContext;
    try {
        boost::asio::io_context ioContext;
        std::list<ServerAsio> servers;
        servers.emplace_back(ioContext, tcp::endpoint(tcp::v4(), SERVER_PORT));
//        servers.emplace_back(ioContext, tcp::endpoint(tcp::v6(), SERVER_PORT));

        ioContext.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
