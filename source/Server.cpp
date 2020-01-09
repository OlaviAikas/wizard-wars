#include "../headers/Server.hpp"



using boost::asio::ip::udp;
Server::Server(boost::asio::io_service &io_service, unsigned short port, Gamestatus *gs)
    : io_service_(io_service),
      socket_(io_service, udp::endpoint(udp::v4(), port))
{
    start_listening();
    game_status = gs;
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
    // if(message.find("Hi, this is Bob") != -1){
    //     std::string answer = "Hi Bob ";
    //     answer += message.substr(message.length()-2,2);
    //     answer += std::string(", this is Aliece");
    //     return answer;
    // } else {
    //     return std::string("Hi Anonymous, this is Alice.");
    // }
    if(message.find("ready") != -1){
        ready=true;
        std::string answer = "go";
        return answer;
    }
    std::stringstream ss;
    ss << "Hi! I am a server's response";
    int player_number = message.front() - '0';
    std::vector<std::string> message_blocks;
    char identifier = message.front();
    switch (identifier)
    {
    case '0': // Player
        /* code */
        break;
    case '1': // Controlpoint
        /* code */
        break;
    case '2': // Spell
        /* code */
        break;
    case '3': // Gameinfo
        /* code */
        
        break;
    default:
        break;
    }
    return ss.str();
}

void Server::send_string(std::string s){
    std::cout << "Server cannot send messages" << std::endl;
}