//
// Created by blue on 3/31/22.
//

#include "ChatSession.hpp"

namespace network_programming {

    void ChatSession::start() {
        this->room.join(shared_from_this());
        doReadHeader();
    }

    ChatSession::ChatSession(tcp::socket socket, ChatRoom &room):
    socket(std::move(socket)), room(room){

    }

    void ChatSession::deliver(const ChatMessage &msg) {
        bool writeInProgress = !writeMsgs.empty();
        writeMsgs.push_back(msg);
        if (!writeInProgress) {
            doWrite();
        }
    }

    void ChatSession::doReadBody() {
        auto self(shared_from_this());
        boost::asio::async_read(this->socket,
                boost::asio::buffer(this->readMsg.body()))
    }


}