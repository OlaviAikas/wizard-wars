
#pragma once
#include <string>
#include "Gamestatus.hpp"
class Interface {
    
    protected:
    public:
    Interface();
    Gamestatus* game_status;
    // event handlers
    virtual void send_message(std::string);

};