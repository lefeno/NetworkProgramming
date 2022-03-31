//
// Created by blue on 3/30/22.
//

#include "Session.hpp"

namespace network_programming {

    Session::Session(tcp::socket socket): socket(std::move(socket)) {
    }

    Session::~Session() {

    }

    void Session::start() {
        doRead();
    }

    void Session::doWrite(std::size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(this->socket,
                boost::asio::buffer(this->dataReceive, length),
                makeCustomAllocHandler(this->memoryHandler, [this, self] (boost::system::error_code errorCode, std::size_t length) {
                  if (!errorCode) {
                      doRead();
                  }
                }));
    }

    void Session::doRead() {
        auto self(shared_from_this());
        this->socket.async_read_some(
                boost::asio::buffer(this->dataReceive),
                makeCustomAllocHandler(this->memoryHandler, [this, self](boost::system::error_code errorCode,
                        std::size_t length) {
                      if (!errorCode) {
                          doWrite(length);
                      }
                }));
    }
}