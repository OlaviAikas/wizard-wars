
#pragma once
#include <string>
#include "Map.hpp"
class Interface {
    
    protected:
        short client_number;
    public:
        Map* map;
        bool ready;
        Interface();
        virtual ~Interface();
        short get_client();
        // event handlers
        virtual void send_string(std::string);

};