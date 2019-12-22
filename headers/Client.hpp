#pragma once
#include "Interface.hpp"
#include <cstdlib>
#include <iostream>
#include <deque>
#include <boost/thread.hpp>
#include <queue>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/atomic.hpp>
#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/mutex.hpp>
#include "Gamestatus.hpp"

using boost::asio::ip::udp;

class Client : public Interface {
    public:
    Client(boost::asio::io_service& io_service, const std::string& host,
     const std::string& port, Gamestatus *gs);
    ~Client();
    
    // methods controling the listening
    void start_listening();
    void listen();

    // methods controling the sending queue
    void start_senders();
    void sender();
    void do_send(std::string message); // send synchronously

    void terminate();
    void run();

    

    // event handler for arriving messages
    void onResponse(std::string message);

    // virtual functions of Interface that are overwritten
    // send a string to the server asynchonously -> onResponse gets called on answer
    void send_string(std::string *msg);

    protected:
    
    private:

    boost::asio::io_service& io_service_; 
    udp::socket socket_; 
    udp::endpoint sender_endpoint_;

    std::queue<std::string*> msg_queue;
    boost::thread_group sender_threads;

    boost::fibers::condition_variable wait_send_cond;
    boost::fibers::mutex wait_send_mtx;

    boost::thread* listen_thread;

};