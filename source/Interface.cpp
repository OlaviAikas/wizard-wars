#include "../headers/Interface.hpp"

Interface::Interface(){
    ready=false;
    client_number=1;
    map=new Map("resources/map.bmp");
}

Interface::~Interface() { }


void Interface::send_string(std::string s){
    
}

short Interface::get_client(){
    return this->client_number;
}