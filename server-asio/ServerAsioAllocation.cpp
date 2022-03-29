//
// Created by blue on 3/30/22.
//

#include "ServerAsioAllocation.h"

namespace network_programming {

    using boost::asio::ip::tcp;

    ServerAsioAllocation::~ServerAsioAllocation() {

    }

    ServerAsioAllocation::ServerAsioAllocation(boost::asio::io_context &ioContext, short port)
    : acceptor(ioContext, tcp::endpoint(tcp::v4(), port)) {

    }

    void ServerAsioAllocation::doAccept() {

    }

}
