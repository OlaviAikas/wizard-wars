#include <cstdlib>
#include <iostream>
#include <deque>
#include <boost/bind.hpp>
#include "asio.hpp"
#include "message.hpp"

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
using asio::ip::udp;
class udp_client{ 
public: 
    udp_client (asio::io_service& io_service, const std::string& host, const std::string& port) 
    :io_service_(io_service), socket_(io_service, udp::endpoint (udp::v4(), 0)) { 
        udp::resolver resolver(io_service_); 
        udp::resolver::query query(udp::v4(), host, port); 
        udp::resolver::iterator itr = resolver.resolve(query);

        sender_endpoint_ = *itr; 
    }

    ~udp_client(){ 
        socket_.close();
    }
    void send_message(const message& msg){
        io_service_.post(boost::bind(&udp_client::do_write, this, msg));
    }

    void do_write(const message& msg){
        send_msg_queue_.push_back(msg);

        if (!send_msg_queue_.empty()){
            socket_.async_send_to(
                asio::buffer(send_msg_queue_.front().data(), send_msg_queue_.front().length()),
                sender_endpoint_,
                boost::bind(&udp_client::handle_send_to, this, 
                asio::placeholders::error,
                asio::placeholders::bytes_transferred));

            std::cout<<"send data(str):"<<show_str(send_msg_queue_.front().data(), send_msg_queue_.front().length())<<std::endl;
        }
    }



    void handle_send_to(const asio::error_code& error, size_t s/*bytes_sent*/){
        

        if (!error){
            // send success, remove from the queue
            send_msg_queue_.pop_front(); 

            // recv response after send a message
            recv_message();

            if (!send_msg_queue_.empty()){
                socket_.async_send_to(
                    asio::buffer(send_msg_queue_.front().data(), send_msg_queue_.front().length()),
                    sender_endpoint_,
                    boost::bind(&udp_client::handle_send_to, this, 
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));
            }
        }
        else{
            std::cerr<<"error in handle_send_to:"<<error<<std::endl;
            socket_.close();
        }

    }

    void recv_message(){
        socket_.async_receive_from(
            asio::buffer(data_.data(), data_.max_length()), sender_endpoint_,
            boost::bind(&udp_client::handle_receive_from, this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
    }

    void handle_receive_from(const asio::error_code& error, size_t bytes_recvd)
    {
        if(!error){
            std::cout<<"recv data(str):"<<show_str(data_.data(), bytes_recvd)<<std::endl;
            if(bytes_recvd > message::header_length)
                data_.body_length(bytes_recvd-message::header_length);
            //std::cout<<"message.lenght()="<<data_.length()<<"bytes_recvd="<<bytes_recvd<<std::endl;
        }
        else{
            std::cerr<<"error in handle_receive_from:"<<error<<std::endl;
            socket_.close();
        }
    }
private: 
    //enum {max_length = 1024};
    //char data_[max_length];
    message data_;
    asio::io_service& io_service_; 
    udp::socket socket_; 
    udp::endpoint sender_endpoint_;
    std::deque<message> send_msg_queue_;
};

int main (int argc, char* argv []) { 

    asio::io_service is; 

    udp_client c1(is, "localhost", "13");
    std::string msg1 = "Hi, this is Bob!";

    message msg;
    msg.body_length(msg1.length());
    memcpy(msg.data(), "1234", message::header_length);
    memcpy(msg.body(), msg1.c_str(), msg.body_length());

    c1.send_message(msg);
    is.run (); 

    return 0; 
}