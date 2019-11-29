#import "Server.hpp"
Server Server::Server(Map* map, short port){
        this->map = map;
        this->port = port;
        udpServer = new udp_server(this->io_service, port, this);

    }