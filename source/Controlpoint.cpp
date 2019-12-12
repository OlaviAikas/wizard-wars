#include "../headers/Controlpoint.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <list>

Controlpoint::Controlpoint(int x, int y, int number, int side, bool owner) : MapObject(x, y, side, side, true) {
    this->number = number;
    this->owner = owner;
    this->havechanged = false;
}

short Controlpoint::get_number() {
    return this->number;
}

bool Controlpoint::get_owner() {
    return this->owner;
}

void Controlpoint::set_owner(short newowner) {
    this->owner = newowner;
    this->havechanged = true;
}

void Controlpoint::on_collision(Player other){
    if (other.get_team()!=owner){
        timegot+=1;
        if (timegot>=timetoget){
            set_owner(other.get_team());
        }
    }
    else{
        if (timegot>0){
            timegot-=1;
        }
    }
    this->havechanged = true;
}