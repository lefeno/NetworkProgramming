//
// Created by blue on 3/30/22.
//

#include "MemoryHandler.h"

namespace network_programming {

    MemoryHandler::MemoryHandler(): {
        this->storageInUse = false;
    }

    MemoryHandler::~MemoryHandler() {
    }

    void *MemoryHandler::allocate(std::size_t size) {
        if (!this->storageInUse && size < sizeof(this->storage)) {
            this->storageInUse = true;
            return &(this->storage);
        } else {
            return ::operator new(size);
        }
    }

    void MemoryHandler::deallocate(void *pointer) {
        if (pointer == &(this->storage)) {
            this->storageInUse = false;
        } else {
            ::operator delete(pointer);
        }
    }


}