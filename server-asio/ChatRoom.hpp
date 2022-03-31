//
// Created by blue on 3/31/22.
//

#ifndef NETWORKPROGRAMMING_CHATROOM_HPP
#define NETWORKPROGRAMMING_CHATROOM_HPP

#include <set>
#include "ChatParticipant.h"

namespace network_programming {

    class ChatRoom {
    public:
        void join(ChatParticipantPtr participant);
        void leave(ChatParticipantPtr participant);
        void deliver(const ChatMessage& msg);
    private:
        std::set<ChatParticipantPtr> participants;
        enum {MaxRecentMsgs = 100};
        ChatMessageQueue recentMsgs;
    };
}

#endif //NETWORKPROGRAMMING_CHATROOM_HPP
