#include "../headers/Map.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"
class Interface {
    
    protected:
        asio::io_service io_service;
        Map* map;
    public:
    Interface(){

    }
    // event handlers
    virtual void on_target_change(){

    }

};