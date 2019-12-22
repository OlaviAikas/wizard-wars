#include "../headers/Server.hpp"



using boost::asio::ip::udp;
Server::Server(boost::asio::io_service &io_service, short port, Gamestatus *gs)
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
    std::stringstream ss;
    ss << *(game_status->playerNumber);
    int player_number = message.front() - '0';
    message.erase(0,1); // remove the player number from the beginning
    std::vector<std::string> message_blocks;
    boost::split(message_blocks, message, boost::is_any_of(":"));
    for(std::vector<std::string>::iterator m = message_blocks.begin(); m != message_blocks.end(); ++m) {
        if(m->size() == 0) continue;
        char identifier = m->front();
        std::vector<std::string> mes;
        bool exists = false;
        switch (identifier)
        {
        case '0': // Player
            
            boost::split(mes, *m, boost::is_any_of("."));
            
            for (std::list<Player*>::iterator i = game_status->map->players.begin(); i != game_status->map->players.end(); i++) {
                if (player_number==std::stoi(mes[1])){
                    (*i)->change_x(std::stoi(mes[2]));
                    (*i)->change_y(std::stoi(mes[3]));
                    (*i)->change_destx(std::stoi(mes[4]));
                    (*i)->change_desty(std::stoi(mes[5]));
                    (*i)->reset_havechanged();
                    exists = true;
                    break;
                }
            }
            // player does not exist yet -> add new player
            if(!exists){
                game_status->map->players.push_back(new Player(std::stoi(mes[2]), std::stoi(mes[3]), std::stoi(mes[1])));
            }
            break;
        case '1': // Controlpoint
            
            break;
        case '2': // Spell
            // todo -> add spells that do not exist yet
            break;
        case '3': // Gameinfo
            if(m->c_str()[1] == '0'){ // client registers and requests number
                connected_players.insert(std::pair<int,int>(connected_players.size() + 1, 0));
                ss << "3" << "0" << connected_players.size() + 1;
            }
            break;
        default:
            break;
        }
    }
    return ss.str();
}

void Server::send_message(std::string s){
    std::cout << "Server cannot send messages" << std::endl;
}
