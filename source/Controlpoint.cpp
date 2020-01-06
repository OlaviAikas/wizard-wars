#include "../headers/Controlpoint.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <list>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

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

void Controlpoint::on_collision(Player &other){
    if (other.get_team()!=owner){
        is_someone=true;
        timegot+=1;
        if (timegot>=timetoget){
            set_owner(other.get_team());
            timegot=0;
        }
    }
    else{
        if (timegot>0){
            timegot-=1;
        }
    }
    this->havechanged = true;
}

void Controlpoint::draw(int camera_x, int camera_y){
    if (not is_someone && timegot>0){
        timegot-=1;
    }
    is_someone=false;
    if (timegot!=0){
        if (owner){
            al_draw_filled_rectangle(x-50-camera_x, y-5-camera_y,x+50-camera_x,y+5-camera_y, al_map_rgb(255,0,0));
		    al_draw_filled_rectangle(x-50-camera_x, y-5-camera_y,x-50-camera_x+100*(timegot)/timetoget,y+5-camera_y, al_map_rgb(0,0,255));
        }
        else{
            al_draw_filled_rectangle(x-50-camera_x, y-5-camera_y,x+50-camera_x,y+5-camera_y, al_map_rgb(0,0,255));
		    al_draw_filled_rectangle(x-50-camera_x, y-5-camera_y,x-50+100*(timegot)/timetoget - camera_x,y+5-camera_y, al_map_rgb(255,0,0));
        }
    }
}