//
// Created by blue on 3/30/22.
//

#include <iostream>
#include "Session.hpp"

#define FUNC_NAME "Session"

namespace network_programming {

    Session::Session(tcp::socket socket, Room& room): socket(std::move(socket)), room(room) {
    }

    Session::~Session() {

    }

    void Session::start() {
        this->room.join(shared_from_this());
        doRead();
    }

    void Session::doWrite(const std::string& msg) {
        auto self(shared_from_this());
        boost::asio::async_write(this->socket,
                boost::asio::buffer(msg, msg.length()),
                [this, self] (boost::system::error_code errorCode, std::size_t length) {
                  if (!errorCode) {
                      doRead();
                  }
                });
    }

    void Session::doRead() {
        auto self(shared_from_this());
        this->dataReceive.fill(0);
        this->socket.async_read_some(
                boost::asio::buffer(this->dataReceive),
                [this, self](boost::system::error_code errorCode,
                        std::size_t length) {
                      std::cout << FUNC_NAME << ":" << "Read message from [" << this->socket.remote_endpoint().address().to_string()
                              << "]:" << this->socket.remote_endpoint().port() << " message "
                              << std::string(this->dataReceive.data()) << " length " << length << std::endl;
                      if (!errorCode) {
                          this->room.deliver(std::string(this->dataReceive.data()));
                      } else {
                          this->room.leave(shared_from_this());
                      }
                });
    }

    void Session::deliver(const std::string &msg) {
        std::cout << FUNC_NAME << ":" << "Deliver message to [" << this->socket.remote_endpoint().address().to_string()
                  << "]:" << this->socket.remote_endpoint().port() << " message " << msg << std::endl;
        doWrite(msg);
    }
}