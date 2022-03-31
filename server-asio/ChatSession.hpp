//
// Created by blue on 3/31/22.
//

#ifndef NETWORKPROGRAMMING_CHATSESSION_HPP
#define NETWORKPROGRAMMING_CHATSESSION_HPP

#include "ChatParticipant.h"
#include "ChatRoom.hpp"
#include <boost/asio.hpp>

namespace network_programming {

    using boost::asio::ip::tcp;

    class ChatSession: public ChatParticipant,
    public std::enable_shared_from_this<ChatSession>{
    public:
        ChatSession(tcp::socket socket, ChatRoom& room);
        void start();
        void deliver(const ChatMessage& msg);
    private:
        void doReadHeader();
        void doReadBody();
        void doWrite();
        tcp::socket socket;
        ChatRoom& room;
        ChatMessage readMsg;
        ChatMessageQueue writeMsgs;
    };
}

#endif //NETWORKPROGRAMMING_CHATSESSION_HPP
