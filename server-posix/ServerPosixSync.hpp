//
// Created by blue on 4/2/22.
//

#ifndef NETWORKPROGRAMMING_SERVERPOSIXSYNC_HPP
#define NETWORKPROGRAMMING_SERVERPOSIXSYNC_HPP

#include <mutex>
#include "ServerPosix.hpp"

namespace network_programming {

    class ServerPosixSync: public ServerPosix {
    public:
        ServerPosixSync(const std::string& host, const std::string& port, const int &socketType);
        void handleConnections(const Socket &listenSocket) override;
    private:
        std::mutex resourceMutex;
        enum {MAX_PRE_THREAD = 5};
    };
}

#endif //NETWORKPROGRAMMING_SERVERPOSIXSYNC_HPP
