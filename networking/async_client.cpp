#include "Client.hpp"
#include "message.hpp"

int main (int argc, char* argv []) { 

    asio::io_service is; 

    Client c1(is, "localhost", "13");
    std::string msg1 = "Hi, this is Bob!";

    message msg;
    msg.body_length(msg1.length());
    memcpy(msg.data(), "1234", message::header_length);
    memcpy(msg.body(), msg1.c_str(), msg.body_length());

    c1.send_message(msg);
    is.run();

    return 0; 
}