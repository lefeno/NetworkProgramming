//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_ALLOCATORHANDLER_H
#define NETWORK_PROGRAMMING_ALLOCATORHANDLER_H

#include "MemoryHandler.hpp"

namespace network_programming {

    template <typename T>
    class AllocatorHandler {
    public:
        explicit AllocatorHandler(MemoryHandler& mem): memoryHandler(mem) {
        }

        template<typename U>
        AllocatorHandler(const AllocatorHandler<U>& other) noexcept: memoryHandler(other.memoryHandler) {
        }

        bool operator==(const AllocatorHandler& other) const noexcept {
            return &(this->memoryHandler) == &(other.memoryHandler);
        }

        bool operator!=(const AllocatorHandler& other) const noexcept {
            return &(this->memoryHandler) != &(other.memoryHandler);
        }

        T* allocate(std::size_t size) const {
            return static_cast<T*>(memoryHandler.allocate(sizeof(T) * size));
        }

        void deallocate(T* ptr) const {
            return (this->memoryHandler).deallocate(ptr);
        }
    private:
        template<typename> friend class AllocatorHandler;
        MemoryHandler& memoryHandler;
    };

}

#endif //NETWORK_PROGRAMMING_ALLOCATORHANDLER_H
