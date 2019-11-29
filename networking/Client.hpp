#pragma once
#include "Interface.hpp"
#include "udp_client.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"

class Client : Interface {
    public:
    Client(Map* map, char* ip, short port);
    void onResponse(std::string message);
    protected:
    
    private:
    udp_client* udpClient;
    short port;
    int ip;
    


};