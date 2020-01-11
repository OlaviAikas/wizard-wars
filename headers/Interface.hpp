
#pragma once
#include <string>
class Interface {
    
    protected:
        short client_number;
    public:
        bool ready;
        Interface();
        short get_client();
        // event handlers
        virtual void send_string(std::string);

};