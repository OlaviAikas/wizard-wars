
#pragma once
#include <string>
#include "Map.hpp"
class Interface {
    
    protected:
        short client_number;
    public:
        Map* map;
        void set_map(Map* &map);
        bool ready;
        Interface();
        short get_client();
        // event handlers
        virtual void send_string(std::string);

};