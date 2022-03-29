//
// Created by blue on 3/28/22.
//

#ifndef NETWORK_PROGRAMMING_SERVERPOSIXPREFORKDESCRIPTORPASS_H
#define NETWORK_PROGRAMMING_SERVERPOSIXPREFORKDESCRIPTORPASS_H

#include <vector>
#include "ServerPosixFork.h"

namespace network_programming {
    struct ChildTrack_t {
        pid_t childPid;
        int childPipeFd;
        int childStatus;    /* 0 = ready */
        long childCount;    /* # connection handle */
    };

    class ServerPosixPreForkDescriptorPass: public ServerPosixFork {
    public:
        ServerPosixPreForkDescriptorPass();
        ~ServerPosixPreForkDescriptorPass();
    private:
        ChildTrack_t forkChild(int listenSockFd);
        void handleConnections(int listenSockFd) override;
        int processChild();
        std::vector<ChildTrack_t> pChildTracker;
    };
}

#endif //NETWORK_PROGRAMMING_SERVERPOSIXPREFORKDESCRIPTORPASS_H
