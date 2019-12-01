#pragma once
#include "Interface.hpp"
#include <cstdlib>
#include <iostream>
#include <deque>
#include <boost/bind.hpp>
#include "asio.hpp"
#include "message.hpp"
using asio::ip::udp;

class Client : Interface {
    public:
    Client(asio::io_service io_service, Map* map, std::string& host, short port);
    ~udp_client();
    
    void do_write(const message& msg);
    void handle_send_to(const asio::error_code& error, size_t s/*bytes_sent*/);
    void recv_message();
    void handle_receive_from(const asio::error_code& error, size_t bytes_recvd);

    void send_message(const message& msg);
    void onResponse(std::string message);

    protected:
    
    private:
    message data_;
    asio::io_service& io_service_; 
    udp::socket socket_; 
    udp::endpoint sender_endpoint_;
    std::deque<message> send_msg_queue_;
    short port;
    std::string& host host;

};