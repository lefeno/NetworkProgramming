//
// Created by blue on 3/30/22.
//

#include <iostream>
#include "ServerAsioAllocation.hpp"
#include "Session.hpp"

namespace network_programming {

    using boost::asio::ip::tcp;

    ServerAsioAllocation::ServerAsioAllocation(boost::asio::io_context &ioContext, short port)
    : serverSocket(ioContext, tcp::endpoint(tcp::v4(), port)) {
        doAccept();
    }

    void ServerAsioAllocation::doAccept() {
        this->serverSocket.async_accept([this] (boost::system::error_code errorCode, tcp::socket socket) {
            std::cout << "Do accept " << socket.max_connections << " " <<
            socket.local_endpoint().port() << " " << socket.remote_endpoint().port() << " "
            << socket.remote_endpoint().address().to_string() << std::endl;
            if(!errorCode) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            doAccept();
        });
    }

}
