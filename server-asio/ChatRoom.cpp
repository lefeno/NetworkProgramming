//
// Created by blue on 3/31/22.
//

#include "ChatRoom.hpp"

namespace network_programming {

    void ChatRoom::join(ChatParticipantPtr participant) {
        this->participants.insert(participant);
        for (auto msg: recentMsgs) {
            participant->deliver(msg);
        }
    }

    void ChatRoom::deliver(const ChatMessage &msg) {
        this->recentMsgs.push_back(msg);
        while (recentMsgs.size() > MaxRecentMsgs) {
            this->recentMsgs.pop_front();
        }
        for (auto participant: participants) {
            participant->deliver(msg);
        }
    }

    void ChatRoom::leave(ChatParticipantPtr participant) {
        this->participants.erase(participant);
    }
}
