//
// Created by blue on 3/28/22.
//

#include <iostream>
#include "ClientChannel.h"

namespace network_programming {
    ClientChannel::ClientChannel() {
        this->mutexLock = PTHREAD_MUTEX_INITIALIZER;
    }

    ClientChannel::~ClientChannel() {

    }

    int ClientChannel::registerObserver(IChannelObserver *observer) {
        pthread_mutex_lock(&this->mutexLock);
        this->observerList.push_back(observer);
        pthread_mutex_unlock(&this->mutexLock);
        return 0;
    }

    int ClientChannel::removeObserver(IChannelObserver *observer) {
        pthread_mutex_lock(&this->mutexLock);
        this->observerList.remove(observer);
        pthread_mutex_unlock(&this->mutexLock);
        return 0;
    }

    int ClientChannel::notifyObserver(void *data, int dataLen) {
        pthread_mutex_lock(&this->mutexLock);
        std::cout << "Notify to all " << this->observerList.size() << " observers " << std::endl;
        for(auto& pObserver : this->observerList) {
            pObserver->update(data, dataLen);
        }
        pthread_mutex_unlock(&this->mutexLock);
        return 0;
    }
}