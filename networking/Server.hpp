#pragma once
#include "Interface.hpp"
#include "udp_server.cpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../headers/Map.hpp"
#include <boost/thread.hpp>
#include <boost/array.hpp>
using boost::asio::ip::udp;
class Server {
    public:
    Server(boost::asio::io_service &io_service, Map* map, short port);
    ~Server();
    // event handlers

    void start_listening();
    void listen();
    void run();
    void terminate();

    protected:
    
    private:
    
    boost::asio::io_service& io_service_;
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];

    short port;
    Map* map;

    boost::thread* listen_thread;

    std::string generateResponse(std::string message);

};
