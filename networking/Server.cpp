#include "Server.hpp"

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



Server::Server(asio::io_service &io_service, Map* map, short port)
    : io_service_(io_service),
      socket_(io_service, udp::endpoint(udp::v4(), port))
{
    memset(data_, 0, max_length);
    socket_.async_receive_from(
        asio::buffer(data_, max_length), sender_endpoint_, 
        boost::bind(&Server::handle_receive_from, this, 
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
}

void Server::handle_receive_from(const asio::error_code& error,
      size_t bytes_recvd)
{
    if (!error && bytes_recvd > 0)
    {
        std::cout<<"recv data(size="<<bytes_recvd<<"):"
            <<show_str(data_, bytes_recvd)<<std::endl;
        std::string request = show_str(data_, bytes_recvd);

        boost::shared_ptr<std::string> message(generateResponse(request));
        socket_.async_send_to(
            asio::buffer(*message), sender_endpoint_, 
            boost::bind(&Server::handle_send_to, this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));

    }
    else
    {
    socket_.async_receive_from(
        asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&Server::handle_receive_from, this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
    }
}

void Server::handle_send_to( const asio::error_code& /*error*/,
      size_t s/*bytes_sent*/)
{
socket_.async_receive_from(
    asio::buffer(data_, max_length), sender_endpoint_,
    boost::bind(&Server::handle_receive_from, this,
    asio::placeholders::error,
    asio::placeholders::bytes_transferred));
    memset(data_, 0, max_length);
}

std::string* Server::generateResponse(std::string message){
    return new std::string("Hi Bob, this is Alice.");
}
