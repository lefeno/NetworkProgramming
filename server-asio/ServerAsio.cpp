//
// Created by blue on 3/30/22.
//

#include <iostream>
#include "ServerAsio.hpp"
#include "Session.hpp"

namespace network_programming {

    using boost::asio::ip::tcp;

    ServerAsio::ServerAsio(boost::asio::io_context &ioContext, const tcp::endpoint& endpoint)
    : listenSocket(ioContext, endpoint) {
        doAccept();
    }

    void ServerAsio::doAccept() {
        this->listenSocket.async_accept([this] (boost::system::error_code errorCode, tcp::socket connectedSocket) {
            std::cout << "Async accept at [" << this->listenSocket.local_endpoint().address().to_string()
                      << "]:"
                      << this->listenSocket.local_endpoint().port() << " from [" << connectedSocket.remote_endpoint().address().to_string()
                      << "]:" << connectedSocket.remote_endpoint().port() << std::endl;
            if(!errorCode) {
                std::make_shared<Session>(std::move(connectedSocket), room)->start();
            }
            doAccept();
        });
    }

}
