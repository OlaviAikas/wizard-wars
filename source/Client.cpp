#include "../headers/Client.hpp"
using boost::asio::ip::udp;

Client::Client(boost::asio::io_service& io_service, const std::string& host,
  const std::string& port, Gamestatus * gs) 
:io_service_(io_service), socket_(io_service, udp::endpoint (udp::v4(), 0)) { 
    udp::resolver resolver(io_service_); 
    udp::resolver::query query(udp::v4(), host, port); 
    udp::resolver::iterator itr = resolver.resolve(query);
    game_status = gs;
    sender_endpoint_ = *itr;
    ready=false;
    start_listening(); 
    start_senders();
}

Client::~Client(){
    terminate();
    socket_.close();
}
void Client::send_string(std::string msg_text){
    std::cout << "send: " << msg_text << std::endl;
    msg_queue.push(&msg_text);
    std::unique_lock<boost::fibers::mutex> lock(wait_send_mtx);
    wait_send_cond.notify_one();
}
void Client::do_send(std::string msg_text){
    std::vector<char> send_buf;
    send_buf.insert(send_buf.begin(),msg_text.begin(),msg_text.end());
    socket_.send_to(boost::asio::buffer(send_buf),sender_endpoint_);
}
void Client::start_listening(){
    listen_thread = new boost::thread(boost::bind(&Client::listen, this));
}
void Client::start_senders(){
    for(int i=0;i<4;i++){
        sender_threads.create_thread(boost::bind(&Client::sender, this));
    }
}
void Client::sender(){
    std::unique_lock<boost::fibers::mutex> lock(wait_send_mtx);
    while(true){
        wait_send_cond.wait(lock);
        if(!msg_queue.empty()){
            do_send(*(msg_queue.front()));
            msg_queue.pop();
        }
        if(!msg_queue.empty()){
            wait_send_cond.notify_one();
        }
    }
}
void Client::terminate(){
    sender_threads.interrupt_all();
    listen_thread->interrupt();
}
void Client::run(){
    listen_thread->join();
    sender_threads.join_all();
}
void Client::listen(){
    
    try {
        // listening loop
        for (;;){
            boost::array<char, 4096> recv_buf;
            boost::system::error_code error;
            size_t size = socket_.receive_from(boost::asio::buffer(recv_buf), sender_endpoint_);
            this->onResponse(std::string(recv_buf.c_array(), size));
        }
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

void Client::onResponse(std::string message){
    std::cout << "The servers response is: " << message << std::endl;
    if (!ready && message.find("readytoo2") != std::string::npos){
        client_number=2;
        connected=true;
    }
    if (!ready && message.find("readytoo3") != std::string::npos){
        client_number=3;
        connected=true;
    }
    if (!ready && message.find("readytoo4") != std::string::npos){
        client_number=4;
        connected=true;
    }
    if(!ready && message.find("go") != std::string::npos){
        ready=true;
    }
    std::vector<std::string> mes;
    for(int a=0; a==10; a++){
        message.erase(0, 1);
    }
    boost::split(mes, message, boost::is_any_of("|"));
    for(unsigned int j=0; j<mes.size(); j++){
        if (ready && mes[j].find("thisisplayer") != std::string::npos){
            (this->map)->decode_players(mes[j], client_number);
        }
        if (ready && mes[j].find("thisisspell") != std::string::npos){
            (this->map)->decode_spells(mes[j]);
        }
    }
    // modify the game depending on message
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
}



