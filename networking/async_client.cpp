#include "async_client.hpp"

int main (int argc, char* argv []) { 

    asio::io_service is; 

    Client c1(is, "localhost", "13");

    c1.send_string("Hi, this is Bob! 1");
    //c1.send_string("Hi, this is Bob! 2");
    is.run();

    return 0; 
}