//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H
#define NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H

#include <boost/asio.hpp>

namespace network_programming {

    class ServerAsioAllocation {
    public:
        ServerAsioAllocation(boost::asio::io_context& ioContext, short port);
        ~ServerAsioAllocation() = default;
    private:
        void doAccept();
        boost::asio::ip::tcp::acceptor serverSocket;
    };

}

#endif //NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H
