//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H
#define NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include "room/Room.hpp"

namespace network_programming {

    using boost::asio::ip::tcp;

    class ServerAsio {
    public:
        ServerAsio(boost::asio::io_service &ioContext, const tcp::endpoint& endpoint);
        ~ServerAsio() = default;
    private:
        void doAccept();
        boost::asio::ip::tcp::acceptor listenSocket;
        Room room;
        tcp::socket connSocket;
    };

}

#endif //NETWORK_PROGRAMMING_SERVERASIOALLOCATION_H
