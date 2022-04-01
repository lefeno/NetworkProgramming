//
// Created by blue on 4/1/22.
//

#ifndef NETWORKPROGRAMMING_ROOM_HPP
#define NETWORKPROGRAMMING_ROOM_HPP

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


#endif //NETWORKPROGRAMMING_ROOM_HPP
