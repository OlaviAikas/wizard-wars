
#pragma once
#include <string>
class Interface {
    
    protected:
    public:
    Interface();
    bool ready;
    // event handlers
    virtual void send_string(std::string);

};