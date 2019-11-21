#include "../headers/Controlpoint.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <list>

Controlpoint::Controlpoint(int x, int y, int number, int range) : MapObject(x, y, 128, 128, false) {
    this->x = x;
    this->y = y;
    this->number = number;
    this->range = range;
}

short Controlpoint::get_number() {
    return this->number;
}

void Controlpoint::set_owner(short newowner) {
    this->owner = newowner;
}

bool Controlpoint::in_capture_range(MapObject other){
    if (sqrt((x-other.get_x())^2+(y-other.get_y())^2)<=range){
        return true;
    }
    else{
        return false;
    }
}

void Controlpoint::capture(Map map){
    for (std::list<Player>::iterator i = map.players.begin(); i != map.players.end(); i++){
        if (in_capture_range(*i)){
            /* To complete, do it by making run one per second checking if there is any other player entering until end of timer, then change owner */
        }
    }
}