//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_ALLOCATORHANDLER_H
#define NETWORK_PROGRAMMING_ALLOCATORHANDLER_H

#include "MemoryHandler.h"

namespace network_programming {
    template <typename T>
    class AllocatorHandler {
    public:
        using valueType = T;
        explicit AllocatorHandler(MemoryHandler& mem);

        template<typename U>
        AllocatorHandler(const AllocatorHandler<U>& other) noexcept;
        bool operator==(const AllocatorHandler& other) const noexcept;
        bool operator!=(const AllocatorHandler& other) const noexcept;
        T* allocate(std::size_t size) const;
        void deallocate(T* ptr) const;
    private:
        template<typename> friend class AllocatorHandler;
        MemoryHandler& memoryHandler;
    };

}

#endif //NETWORK_PROGRAMMING_ALLOCATORHANDLER_H
