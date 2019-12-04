#include "Server.hpp"



using boost::asio::ip::udp;
Server::Server(boost::asio::io_service &io_service, Map* map, short port)
    : io_service_(io_service),
      socket_(io_service, udp::endpoint(udp::v4(), port))
{
    start_listening();
}
Server::~Server(){
    terminate();
    socket_.close();
}

void Server::start_listening(){
    listen_thread = new boost::thread(boost::bind(&Server::listen, this));
}
void Server::run(){
    listen_thread->join();
}
void Server::terminate(){
    listen_thread->interrupt();
}
void Server::listen(){
    try {

        // listening loop
        for (;;){
            boost::array<char, 1024> recv_buf;
            boost::system::error_code error;
            size_t size = socket_.receive_from(boost::asio::buffer(recv_buf), sender_endpoint_);
            std::cout << std::string(recv_buf.c_array(), size) << std::endl;
            std::string message = this->generateResponse(std::string(recv_buf.c_array(), size));

            boost::system::error_code ignored_error;
            socket_.send_to(boost::asio::buffer(message),
                sender_endpoint_, 0, ignored_error);
        }
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

std::string Server::generateResponse(std::string message){
    if(message.find("Hi, this is Bob") != -1){
        std::string answer = "Hi Bob ";
        answer += message.substr(message.length()-2,2);
        answer += std::string(", this is Aliece");
        return answer;
    } else {
        return std::string("Hi Anonymous, this is Alice.");
    }
}
