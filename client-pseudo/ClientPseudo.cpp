//
// Created by blue on 4/1/22.
//

#include <string>
#include <thread>
#include <iostream>
#include <sstream>
#include "ClientPseudo.hpp"

namespace network_programming {

    ClientPseudo::ClientPseudo(const std::string &remoteHost, const std::string &port, const int& socketType) {
        std::shared_ptr<Connection> pConn = std::make_shared<Connection>(remoteHost, port, socketType);
        std::thread clientHandle([pConn] (const std::shared_ptr<Connection>&) {
                try {
                    //TODO: should push log to files here
                    std::stringstream stream;
                    stream << "Hello message from " << pConn->getSocketFd() << std::endl;
                    std::cout << stream.str();
                    pConn->write(stream.str());
                    while (true) {
                        std::string dataRead = pConn->read();
                        if (dataRead.empty()) {
                            pConn->close();
                            return;
                        }
                    }
                } catch (std::exception& e) {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }

        }, pConn);
        clientHandle.detach();
    }

}