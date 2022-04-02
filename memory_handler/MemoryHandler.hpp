//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_MEMORYHANDLER_H
#define NETWORK_PROGRAMMING_MEMORYHANDLER_H

#include <boost/asio.hpp>

namespace network_programming {
    class MemoryHandler {
    public:
        MemoryHandler();
        ~MemoryHandler();
        MemoryHandler(const MemoryHandler&) = delete;
        MemoryHandler& operator=(const MemoryHandler&) = delete;

        void* allocate(std::size_t size);
        void deallocate(void* pointer);
    private:
        enum {CUSTOM_ALLOCATION_STORAGE_SIZE = 1024};
        typename std::aligned_storage<CUSTOM_ALLOCATION_STORAGE_SIZE>::type storage;
        bool storageInUse;
    };
}

#endif //NETWORK_PROGRAMMING_MEMORYHANDLER_H
