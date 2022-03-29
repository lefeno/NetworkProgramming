//
// Created by blue on 3/28/22.
//

#ifndef NETWORKPROGRAMMING_CLIENTCHANNEL_H
#define NETWORKPROGRAMMING_CLIENTCHANNEL_H

#include "IChannel.h"
#include <list>
#include <pthread.h>

namespace network_programming {
    class ClientChannel: public IChannel {
    public:
        ClientChannel();
        ~ClientChannel();
        int registerObserver(IChannelObserver* observer) override;
        int removeObserver(IChannelObserver *observer) override;
        int notifyObserver(void *data, int dataLen) override;
    private:
        std::list<IChannelObserver*> observerList;
        pthread_mutex_t mutexLock;
    };
}

#endif //NETWORKPROGRAMMING_CLIENTCHANNEL_H
