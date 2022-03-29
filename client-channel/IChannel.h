//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_ICHANNEL_H
#define NETWORK_PROGRAMMING_ICHANNEL_H

#include "IChannelObserver.h"

namespace network_programming {
    class IChannel {
    public:
        virtual ~IChannel(){};
        virtual int registerObserver(IChannelObserver* observer) = 0;
        virtual int removeObserver(IChannelObserver* observer) = 0;
        virtual int notifyObserver(void* data, int dataLen) = 0;
    };
}

#endif //NETWORK_PROGRAMMING_ICHANNEL_H
