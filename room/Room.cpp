//
// Created by blue on 4/1/22.
//

#include "Room.hpp"

namespace network_programming {
    void Room::join(ParticipantPtr participantPtr) {
        participants.insert(participantPtr);
    }

    void Room::deliver(const std::string& msg) {
        for (auto participant: participants) {
            participant->deliver(msg);
        }
    }

    void Room::leave(ParticipantPtr participantPtr) {
        participants.erase(participantPtr);
    }
}