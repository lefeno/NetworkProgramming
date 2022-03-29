//
// Created by blue on 3/30/22.
//

#include "AllocatorHandler.h"

namespace network_programming {
    template<typename T>
    AllocatorHandler<T>::AllocatorHandler(MemoryHandler& mem) {
        this->memoryHandler(mem);
    }

    template<typename T>
    void AllocatorHandler<T>::deallocate(T *ptr) const {

    }


}