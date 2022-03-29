//
// Created by blue on 3/28/22.
//

#include <sys/socket.h>
#include <iostream>
#include "ClientController.h"

namespace network_programming {
    ClientController::~ClientController() {

    }

    ClientController::ClientController() {
        this->channel = nullptr;
    }

    int ClientController::update(void *data, int dataLen) {
        auto bytesSent = ::send(this->connectedSocketFd, data, dataLen, 0);
        std::cout << "Send to sockFd " << this->connectedSocketFd << " bytes " << bytesSent << std::endl;
        return 0;
    }

    int ClientController::registerChannel(IChannel *channel) {
        this->channel = channel;
        this->channel->registerObserver(this);
        return 0;
    }

    ClientController::ClientController(int connectSockFd) {
        this->connectedSocketFd = connectSockFd;
    }

    int ClientController::deregisterChannel(IChannel *channel) {
        this->channel->removeObserver(this);
        return 0;
    }


}