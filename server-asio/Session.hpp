//
// Created by blue on 3/30/22.
//

#ifndef NETWORKPROGRAMMING_SESSION_HPP
#define NETWORKPROGRAMMING_SESSION_HPP

#include "CustomAllocHandler.h"
#include "boost/asio.hpp"

#define MAX_DATA_RECV   1024

namespace network_programming {

    using boost::asio::ip::tcp;

    class Session: public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket);
        ~Session();
        void start();
    private:
        void doRead();
        void doWrite(std::size_t length);
        tcp::socket socket;
        std::array<char, MAX_DATA_RECV> dataReceive;
        MemoryHandler memoryHandler;
    };
}

#endif //NETWORKPROGRAMMING_SESSION_HPP
