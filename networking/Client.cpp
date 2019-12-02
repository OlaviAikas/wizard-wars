#include "Client.hpp"
using asio::ip::udp;
std::string show_hex(const char* data, size_t size)
{
    std::string hex;
    char buf[16];
    const char* p = data;
    for (size_t i = 0; i < size; ++i) {
        std::sprintf(buf, "%02X ", static_cast<unsigned>(p[i]) & 0xFF);
        hex += buf;
    }
    return hex;
}
std::string show_str(const char* data, size_t size)
{
    std::string str;
    char buf[16];
    const char* p = data;
    for (size_t i = 0; i < size; ++i) {
        std::sprintf(buf, "%c", p[i]);
        str += buf;
    }
    return str;
}


Client::Client(asio::io_service& io_service, const std::string& host,  const std::string& port) 
:io_service_(io_service), socket_(io_service, udp::endpoint (udp::v4(), 0)) { 
    udp::resolver resolver(io_service_); 
    udp::resolver::query query(udp::v4(), host, port); 
    udp::resolver::iterator itr = resolver.resolve(query);

    sender_endpoint_ = *itr; 
}

Client::~Client(){ 
    socket_.close();
}
void Client::send_message(const message& msg){
    io_service_.post(boost::bind(&Client::do_write, this, msg));
}

void Client::do_write(const message& msg){
    
    send_msg_queue_.push_back(msg);

    if (!send_msg_queue_.empty()){
        
        socket_.async_send_to(
            asio::buffer(send_msg_queue_.front().data(), send_msg_queue_.front().length()),
            sender_endpoint_,
            boost::bind(&Client::handle_send_to, this, 
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));

        //std::cout<<"send data(str):"<<show_str(send_msg_queue_.front().data(), send_msg_queue_.front().length())<<std::endl;
    }
}



void Client::handle_send_to(const asio::error_code& error, size_t s/*bytes_sent*/){
    

    if (!error){
        // send success, remove from the queue
        send_msg_queue_.pop_front(); 
        std::cout << "do write" << std::endl;

        // recv response after send a message
        recv_message();

        if (!send_msg_queue_.empty()){
            socket_.async_send_to(
                asio::buffer(send_msg_queue_.front().data(), send_msg_queue_.front().length()),
                sender_endpoint_,
                boost::bind(&Client::handle_send_to, this, 
                asio::placeholders::error,
                asio::placeholders::bytes_transferred));
        }
    }
    else{
        std::cerr<<"error in handle_send_to:"<<error<<std::endl;
        socket_.close();
    }

}

void Client::recv_message(){
    socket_.async_receive_from(
        asio::buffer(data_.data(), data_.max_length()), sender_endpoint_,
        boost::bind(&Client::handle_receive_from, this,
        asio::placeholders::error,
        asio::placeholders::bytes_transferred));
}

void Client::handle_receive_from(const asio::error_code& error, size_t bytes_recvd)
{
    if(!error){
        //std::cout<<"recv data(str):"<<show_str(data_.data(), bytes_recvd)<<std::endl;
        if(bytes_recvd > message::header_length)
            data_.body_length(bytes_recvd-message::header_length);
        //std::cout<<"message.lenght()="<<data_.length()<<"bytes_recvd="<<bytes_recvd<<std::endl;
        onResponse(data_.data());
    }
    else{
        std::cerr<<"error in handle_receive_from:"<<error<<std::endl;
        socket_.close();
    }
}

void Client::onResponse(std::string message){
    std::cout << "The servers response is: " << message << std::endl;
}


void Client::send_string(const std::string msg_text){
    message msg;
    msg.body_length(msg_text.length());
    memcpy(msg.data(), "", message::header_length);
    memcpy(msg.body(), msg_text.c_str(), msg.body_length());
    send_message(msg);
}