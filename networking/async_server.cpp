#include "async_server.hpp"

int main()
{
  try
  {

    boost::asio::io_service io_service;

    Server s(io_service, (short) 13);
    s.run();
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

// server.cpp
// ~~~~~~~~~~

// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
