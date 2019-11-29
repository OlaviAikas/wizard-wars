#pragma once
#include "Interface.hpp"
#include "udp_server.cpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"

class Server : Interface {
    public:
    Server(Map* map, short port);
    std::string generateResponse(std::string message);
    protected:
    
    private:
    udp_server* udpServer;
    short port;
    


};