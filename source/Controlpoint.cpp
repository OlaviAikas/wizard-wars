#include "../headers/Controlpoint.hpp"


Controlpoint::Controlpoint(int x, int y, int number, int side, bool owner) : MapObject(x, y, side, side, true) {
    this->number = number;
    this->owner = owner;
    this->havechanged = false;
}

bool Controlpoint::get_havechanged(){
    this->havechanged;
}
void Controlpoint::reset_havechanged(){
    this->havechanged=false;
}

short Controlpoint::get_number() {
    return this->number;
}

bool Controlpoint::get_owner() {
    return this->owner;
}

void Controlpoint::change_owner(bool updated){
    this->owner=updated;
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
int Controlpoint::get_timegot(){
    return timegot;
}
int Controlpoint::get_timetoget(){
    return timetoget;
}
void Controlpoint::change_tgot(int tgot){
    this->timegot=tgot;
}
void Controlpoint::change_ttoget(int ttoget){
    this->timetoget=ttoget;
}