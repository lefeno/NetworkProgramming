//
// Created by blue on 4/1/22.
//

#ifndef NETWORKPROGRAMMING_PARTICIPANT_H
#define NETWORKPROGRAMMING_PARTICIPANT_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <deque>

namespace network_programming {

    class Participant {
    public:
        virtual ~Participant() = default;
        virtual void deliver(const std::string& msg) = 0;
    };

    typedef std::shared_ptr<Participant> ParticipantPtr ;
}

#endif //NETWORKPROGRAMMING_PARTICIPANT_H
