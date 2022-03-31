//
// Created by blue on 3/31/22.
//

#ifndef NETWORKPROGRAMMING_CHATPARTICIPANT_H
#define NETWORKPROGRAMMING_CHATPARTICIPANT_H

#include <deque>
#include <string>
#include <bits/shared_ptr.h>

namespace network_programming {

    typedef std::string ChatMessage ;
    typedef std::deque<ChatMessage> ChatMessageQueue;

    class ChatParticipant {
    public:
        virtual ~ChatParticipant() = default;
        virtual void deliver(const ChatMessage& msg) {};
    };
    typedef std::shared_ptr<ChatParticipant> ChatParticipantPtr ;
}

#endif //NETWORKPROGRAMMING_CHATPARTICIPANT_H
