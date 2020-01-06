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
}

short Controlpoint::get_number() {
    return this->number;
}

bool Controlpoint::get_owner() {
    return this->owner;
}

void Controlpoint::set_owner(short newowner) {
    this->owner = newowner;
}

void Controlpoint::on_collision(Player &other){
		if (other.get_team()!=owner) {
			contested = true;
			if (other.get_team() == 1) {//Team 1 goes into the positive
				timegot +=1;
				if (timegot>=timetoget){
                    set_owner(1);
                    timegot=timetoget;
                }
            }
			if (other.get_team() == 2) {//For team 2, we go into the negatives
				timegot +=-1;
				if (timegot<=timetoget){
			      set_owner(2);
			      timegot=-timetoget;
                }
			}
			if (timegot == 0){
				set_owner(0);//This means that the point is neutral
			}//You have to 'undo' the control from the opposing team in order to
		}
    }

void Controlpoint::draw(int camera_x, int camera_y){
    if (owner == 1 && (timegot < timetoget)) {
	    	timegot +=1;
	    }
	else if(owner == 2 && (timegot < -timetoget)){
	    	timegot +=-1;
	}
	if (owner == 1){
		al_draw_bitmap(control_blue, x - camera_x, y - camera_y, 0);
	}
	else if (owner == 2){
		al_draw_bitmap(control_red, x - camera_x, y - camera_y, 0);
	}
	else if (owner == 0){
		al_draw_bitmap(control_neutral, x - camera_x, y - camera_y, 0);
	}
	//This bar shows the progression of how the teams are capturing the control point
	al_draw_filled_rectangle(x-camera_x, y+10-camera_y,x+50-camera_x + 50*(timegot)/timetoget,y+15-camera_y, al_map_rgb(255,0,0));
	al_draw_filled_rectangle(x+50-camera_x-50*(timegot)/timetoget, y+10-camera_y,x+100-camera_x,y+15-camera_y, al_map_rgb(0,0,255));
}
