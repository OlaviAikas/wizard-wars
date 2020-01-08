#include "async_client.hpp"

int main (int argc, char* argv []) { 

    boost::asio::io_service is; 

    Client c1(is, "localhost", "13");
    
    for(int i=0;i<100;i++){
        std::string* msg = new std::string("Hi, this is Bob! ");
        *msg += std::to_string(i);
        c1.send_string(msg);
    }
    
    c1.run();
    //sis.run();

    return 0; 
}