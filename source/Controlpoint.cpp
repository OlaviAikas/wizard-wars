#include "../headers/Controlpoint.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <list>

Controlpoint::Controlpoint(int x, int y, int number, int side, bool owner) : MapObject(x, y, side, side, true) {
    this->number = number;
    this->owner = owner;
}

short Controlpoint::get_number() {
    return this->number;
}

int Controlpoint::get_owner() {
    if (this->owner==true){
        return 0;
    }
    else{
        return 1;
    }
}

int Controlpoint::get_timegot(){
    return this->timegot;
}

int Controlpoint::get_timetoget(){
    return this->timetoget;
}

void Controlpoint::set_owner(short newowner) {
    this->owner = newowner;
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
}