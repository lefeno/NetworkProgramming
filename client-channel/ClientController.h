//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_CLIENTCONTROLLER_H
#define NETWORK_PROGRAMMING_CLIENTCONTROLLER_H

#include "IChannelObserver.h"
#include "IChannel.h"

namespace network_programming {
    class ClientController: public IChannelObserver {
    public:
        ~ClientController();
        ClientController();
        explicit ClientController(int connectSockFd);
        int registerChannel(IChannel* channel);
        int deregisterChannel(IChannel* channel);
        int update(void *data, int dataLen) override;
    private:
        IChannel* channel;
        int connectedSocketFd;
    };
}

#endif //NETWORKPROGRAMMING_CLIENTCONTROLLER_H
