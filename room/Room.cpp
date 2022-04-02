//
// Created by blue on 4/1/22.
//

#include "Room.hpp"

namespace network_programming {
    void Room::join(ParticipantPtr participantPtr) {
        this->roomMutex.lock();
        this->participants.insert(participantPtr);
        this->roomMutex.unlock();
    }

    void Room::deliver(const std::string& msg) {
        for (auto participant: participants) {
            participant->deliver(msg);
        }
    }

    void Room::leave(ParticipantPtr participantPtr) {
        this->roomMutex.lock();
        this->participants.erase(participantPtr);
        this->roomMutex.unlock();
    }

}