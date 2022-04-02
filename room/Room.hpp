//
// Created by blue on 4/1/22.
//

#ifndef NETWORK_PROGRAMMING_ROOM_HPP
#define NETWORK_PROGRAMMING_ROOM_HPP

#include <set>
#include "Participant.h"

namespace network_programming {

    class Room {
    public:
        void join(ParticipantPtr participantPtr);
        void deliver(const std::string& msg);
        void leave(ParticipantPtr participantPtr);
    private:
        std::set<ParticipantPtr> participants;
    };
}


#endif //NETWORK_PROGRAMMING_ROOM_HPP
