//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_SESSION_HPP
#define NETWORK_PROGRAMMING_SESSION_HPP

#include "memory_handler/CustomAllocHandler.h"
#include "boost/asio.hpp"
#include "room/Participant.h"
#include "room/Room.hpp"

namespace network_programming {

    using boost::asio::ip::tcp;

    class Session: public Participant, public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, Room& room);
        ~Session();
        void start();
    private:
        void deliver(const std::string& msg) override ;
        void doRead();
        void doWrite(const std::string& msg);
        tcp::socket socket;
        enum {MAX_DATA_RECV = 1024};
        std::array<char, MAX_DATA_RECV> dataReceive;
        Room& room;
    };
}

#endif //NETWORK_PROGRAMMING_SESSION_HPP
