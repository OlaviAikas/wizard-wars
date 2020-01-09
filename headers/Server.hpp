#pragma once
#include "Interface.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Map.hpp"
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include "Gamestatus.hpp"
#include <map>
using boost::asio::ip::udp;
class Server : public Interface{
    public:
    Server(boost::asio::io_service &io_service, unsigned short port, Gamestatus *gs);
    ~Server();
    // event handlers

    void start_listening();
    void listen();
    void run();
    void terminate();


    // virtual functions of Interface that are overwritten
    void send_message(std::string);

    protected:
    
    private:
    
    boost::asio::io_service& io_service_;
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];

    Gamestatus *game_status;

    unsigned short port;

    boost::thread* listen_thread;

    std::string generateResponse(std::string message);


    std::map<int,int> connected_players;

};
