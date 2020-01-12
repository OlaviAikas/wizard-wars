#include "../headers/Server.hpp"



using boost::asio::ip::udp;
Server::Server(boost::asio::io_service &io_service, unsigned short port, Gamestatus *gs, short number_players)
    : io_service_(io_service),
      socket_(io_service, udp::endpoint(udp::v4(), port))
{
    players_connected=1;
    start_listening();
    game_status = gs;
    ready=false;
    this->number_players=number_players;
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
            boost::array<char, 4096> recv_buf;
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
    // std::cout<<message<<std::endl;
    if((!ready) && message.find("ready") != std::string::npos){
        players_connected++;
        std::cout<<"readytoo"<<std::endl;
        std::string answer = "aaaaaaaaaaareadytoo"+std::to_string(players_connected);
        std::cout<<answer<<std::endl;
        if(players_connected==number_players){
            ready=true;
            answer="aaaaaaaaaaago"+std::to_string(players_connected);
        }
        return answer;
    }
    if(message.find("stillthere") != std::string::npos){
        if(ready){
            return("aaaaaaaaaago"+std::to_string(players_connected));
        }
        return("yup");
    }
    if(message.find("thisisplayer") != std::string::npos){
        bool spell=false;
        int sender=(this->map)->decode_players(message, client_number);
        std::string s="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaathisisplayer:";
        for(std::list<Player*>::iterator i = (this->map)->players.begin(); i != (this->map)->players.end(); i++){
            s=s+((*i)->encode_player())+":";
        }
        s.pop_back();
        s=s+"|";
        for (std::list<Spell*>::iterator i = (this->map)->spells.begin(); i != (this->map)->spells.end(); i++){
            if(!(*i)->transmitted[sender]){
                spell=true;
                (*i)->transmitted[sender]=true;
                s=s+(*i)->encode_spell()+":";
            }
        }
        s.pop_back();
        return s;
    }

    if(message.find("thisisspell") != std::string::npos){
        (this->map)->decode_spells(message);
    }
    //return "ok Boomer";
    /*if(std::stoi(mes[0])==1){
        Map::decode_controlpoints(message);
    }
    if(std::stoi(mes[0])==2){
        Map::decode_spells(message);
    }*/

    //std::stringstream ss;
    //ss << "Hi! I am a server's response";
    //int player_number = message.front() - '0';
    //std::vector<std::string> message_blocks;
    //char identifier = message.front();
    //switch (identifier)
    //{
    //case '0': // Player
        /* code */
        //break;
    //case '1': // Controlpoint
        /* code */
        //break;
    //case '2': // Spell
        /* code */
        //break;
    //case '3': // Gameinfo
        /* code */
        
        //break;
    //default:
        //break;
    //}
    //return ss.str();
    return "";
}

void Server::send_string(std::string s){
    std::cout << "Server cannot send messages" << std::endl;
}
