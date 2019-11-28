#include "Interface.cpp"
#include "udp_server.cpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"

class Server : Interface {
    public:
    Server(Map* map, short port){
        this->map = map;
        this->port = port;
        udpServer = new udp_server(this->io_service, port, this);

    };
    std::string generateResponse(std::string message){
    
    }
    protected:
    
    private:
    udp_server* udpServer;
    short port;
    


};