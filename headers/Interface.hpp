
#pragma once
#include <string>
class Interface {
    
    protected:
    public:
        bool ready;
        Interface();
        // event handlers
        virtual void send_string(std::string);

};