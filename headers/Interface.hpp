
#pragma once
#include <string>
class Interface {
    
    protected:
    public:
        bool ready;
        Interface();
        virtual ~Interface();
        // event handlers
        virtual void send_string(std::string);

};