//
// Created by blue on 3/30/22.
//

#ifndef NETWORK_PROGRAMMING_CUSTOMALLOCHANDLER_H
#define NETWORK_PROGRAMMING_CUSTOMALLOCHANDLER_H

#include "AllocatorHandler.h"

namespace network_programming {

    template<typename Handler>
    class CustomAllocHandler {
    public:
        CustomAllocHandler(MemoryHandler& memory, Handler handler):
        memoryHandler(memory), handler(handler) {
        }

        AllocatorHandler<Handler> getAllocator() const noexcept {
            return AllocatorHandler<Handler>(MemoryHandler());
        }

        template<typename ...Args>
        void operator()(Args&&... args) {
            this->handler(std::forward<Args>(args)...);
        }
    private:
        MemoryHandler& memoryHandler;
        Handler handler;
    };

    template<typename Handler>
    inline CustomAllocHandler<Handler> makeCustomAllocHandler(MemoryHandler& memory, Handler handler) {
        return CustomAllocHandler<Handler>(memory, handler);
    }

}


#endif //NETWORK_PROGRAMMING_CUSTOMALLOCHANDLER_H
