#include "../headers/Zone.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>

Zone::Zone(int start_x, int start_y, int width, int height, bool noclip)
        : Spell(start_x,  start_y,  0,  0, width, height, noclip) {
    // this->number = number;
    this->hit_animation=false;
}

void Zone::move() {}
void Zone::draw(int camera_x, int camera_y) { }
std::string Zone::encode_spell(){
    std::string s="aaaaaaaaaaaaaaaaaaaaaaaaaaaaathisisspell;"+std::to_string(id)+";0;"+std::to_string(transmitted[1])+";"+std::to_string(transmitted[2])+";"+std::to_string(transmitted[3])+";"+std::to_string(transmitted[4])+";"+std::to_string(transmitted[5])+";";
    s=s+element+";";
    s=s+std::to_string(x)+";"+std::to_string(y);
    return s;
}