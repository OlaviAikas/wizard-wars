// async_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"
std::string show_hex(const char* data, size_t size)
{
    std::string hex;
    char buf[16];
    const char* p = data;
    for (size_t i = 0; i < size; ++i) {
        std::sprintf(buf, "%02X ", static_cast<unsigned>(p[i]) & 0xFF);
        hex += buf;
    }
    return hex;
}
std::string show_str(const char* data, size_t size)
{
    std::string str;
    char buf[16];
    const char* p = data;
    for (size_t i = 0; i < size; ++i) {
        std::sprintf(buf, "%c", p[i]);
        str += buf;
    }
    return str;
}
using asio::ip::udp;

class udp_server
{
public:
  udp_server(asio::io_service& io_service, short port)
    : io_service_(io_service),
      socket_(io_service, udp::endpoint(udp::v4(), port))
  {
    memset(data_, 0, max_length);

    socket_.async_receive_from(
        asio::buffer(data_, max_length), sender_endpoint_, 
        boost::bind(&udp_server::handle_receive_from, this, 
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));
  }

  void handle_receive_from(const asio::error_code& error,
      size_t bytes_recvd)
  {
    if (!error && bytes_recvd > 0)
    {
        std::cout<<"recv data(size="<<bytes_recvd<<"):"
            <<show_str(data_, bytes_recvd)<<std::endl
            <<"["<<show_hex(data_, bytes_recvd)<<"]"<<std::endl;

        boost::shared_ptr<std::string> message(
          new std::string("Hi Bob, this is Alice!"));
        socket_.async_send_to(
            asio::buffer(*message), sender_endpoint_, 
            boost::bind(&udp_server::handle_send_to, this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));

    }
    else
    {
      socket_.async_receive_from(
          asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&udp_server::handle_receive_from, this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
    }
  }

  void handle_send_to( const asio::error_code& /*error*/,
      size_t s/*bytes_sent*/)
  {
    socket_.async_receive_from(
        asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&udp_server::handle_receive_from, this,
        asio::placeholders::error,
        asio::placeholders::bytes_transferred));
    memset(data_, 0, max_length);
  }

private:
  asio::io_service& io_service_;
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_udp_echo_server <port>\n";
      return 1;
    }

    asio::io_service io_service;

    using namespace std; // For atoi.
    udp_server s(io_service, atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}