//
// Created by blue on 3/31/22.
//

#ifndef NETWORKPROGRAMMING_CHATSERVER_HPP
#define NETWORKPROGRAMMING_CHATSERVER_HPP

#include <boost/asio.hpp>

namespace network_programming {
    using boost::asio::ip::tcp;

    class ChatServer {
    public:
        ChatServer(boost::asio::io_context& ioContext,
                const tcp::endpoint);
    private:
        void doAccept();
        tcp::acceptor socket;

    };
}

#endif //NETWORKPROGRAMMING_CHATSERVER_HPP
