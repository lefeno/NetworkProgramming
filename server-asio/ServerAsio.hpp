//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H
#define NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H

#include <boost/asio.hpp>
#include "Room.hpp"

namespace network_programming {

    using boost::asio::ip::tcp;

    class ServerAsio {
    public:
        ServerAsio(boost::asio::io_context& ioContext, const tcp::endpoint& endpoint);
        ~ServerAsio() = default;
    private:
        void doAccept();
        boost::asio::ip::tcp::acceptor listenSocket;
        Room room;
    };

}

#endif //NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H
