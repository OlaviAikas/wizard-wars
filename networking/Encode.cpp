#include "boost/asio.hpp"
using namespace boost::asio;

...

io_service io_service;
ip::udp::socket socket(io_service);
ip::udp::endpoint remote_endpoint;

socket.open(ip::udp::v4());

remote_endpoint = ip::udp::endpoint(ip::address::from_string("192.168.0.4"), 9000);

boost::system::error_code err;
socket.send_to(buffer("Bob Dave", 8), remote_endpoint, 0, err);

socket.close();