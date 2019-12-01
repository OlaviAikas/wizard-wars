#pragma once
#include "Interface.hpp"
#include "udp_server.cpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"
#include "../headers/Map.hpp"


using asio::ip::udp;

class Server {
    public:
    Server(asio::io_service &io_service, Map* map, short port);
    
    // event handlers

    void handle_receive_from(const asio::error_code& error,
        size_t bytes_recvd);

    void handle_send_to( const asio::error_code& /*error*/,
        size_t s/*bytes_sent*/);

    protected:
    
    private:
    
    asio::io_service& io_service_;
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];

    short port;
    Map* map;

    std::string* generateResponse(std::string message);

};
