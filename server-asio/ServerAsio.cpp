//
// Created by blue on 3/30/22.
//

#include <iostream>
#include "ServerAsio.hpp"
#include "Session.hpp"

namespace network_programming {

    using boost::asio::ip::tcp;

    ServerAsio::ServerAsio(boost::asio::io_service &ioContext, const tcp::endpoint& endpoint)
    : listenSocket(ioContext, endpoint), connSocket(ioContext) {
        boost::system::error_code ec;
        this->listenSocket.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true), ec);
        doAccept();
    }

    void ServerAsio::doAccept() {
        this->listenSocket.async_accept(this->connSocket, [this] (boost::system::error_code errorCode) {
            if(!errorCode) {
                std::cout << "Async accept at [" << this->listenSocket.local_endpoint().address().to_string()
                          << "]:"
                          << this->listenSocket.local_endpoint().port() << " from [" << this->connSocket.remote_endpoint().address().to_string()
                          << "]:" << this->connSocket.remote_endpoint().port() << std::endl;
                std::make_shared<Session>(std::move(this->connSocket), room)->start();
            }
            doAccept();
        });
    }

}
