//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_ICHANNELOBSERVER_H
#define NETWORK_PROGRAMMING_ICHANNELOBSERVER_H

namespace network_programming {
    class IChannelObserver {
    public:
        virtual ~IChannelObserver(){};
        virtual int update(void* data, int dataLen) = 0;
    };
}

#endif //NETWORK_PROGRAMMING_ICHANNELOBSERVER_H
