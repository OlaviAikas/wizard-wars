#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"
#include "Server.hpp"

using asio::ip::udp;


class udp_server
{
public:
  Server* server;
  udp_server(asio::io_service& io_service, short port, Server* server);

  void handle_receive_from(const asio::error_code& error,
      size_t bytes_recvd);

  void handle_send_to( const asio::error_code& /*error*/,
      size_t s/*bytes_sent*/);

private:
  asio::io_service& io_service_;
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};