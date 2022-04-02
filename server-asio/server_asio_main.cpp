#include <iostream>
#include "server-asio/ServerAsio.hpp"
#include <list>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_service ioContext;
    const int SERVER_PORT = 8080;
    try {
        boost::asio::io_service ioContext;
        std::list<network_programming::ServerAsio> servers;
        servers.emplace_back(ioContext, tcp::endpoint(tcp::v4(), SERVER_PORT));
//        servers.emplace_back(ioContext, tcp::endpoint(tcp::v6(), SERVER_PORT));

        ioContext.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
