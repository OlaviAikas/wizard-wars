#include "async_server.hpp"

int main()
{
  try
  {

    asio::io_service io_service;

    Server s(io_service, 0, (short) 13);

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}