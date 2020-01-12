//#define DEBUG_MODE
#include "../headers/MapObject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cmath>

MapObject::MapObject(int x, int y, int width, int height, bool noclip) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->noclip = noclip;
    this->havechanged = false;
    this->garbage_collect = false;
    this->drawsprite=true;
    this->transmitted[1]=true;

}

MapObject::~MapObject(){ }
void MapObject::move() { std::cout << "momove" << std::endl; havechanged=true;}

std::string MapObject::encode_spell(){
    
}

void MapObject::set_x(int x) {
    this->x=x;
}

void MapObject::set_y(int y) {
    this->y=y;
}

int MapObject::get_x() const {
    return x;
}

int MapObject::get_y() const {
    return y;
}

int MapObject::get_width() const {
    return width;
}

int MapObject::get_height() const {
    return height;
}

int MapObject::get_next_x(){
	return this->x;
}

int MapObject::get_next_y(){
	return this->y;
}

int MapObject::get_speed(){
	return 0;
}

bool MapObject::get_garbage_collect() const {
    return garbage_collect;
}

bool MapObject::get_noclip() const {
    return noclip;
}

void MapObject::hit(const int amount) {
#ifdef DEBUG_MODE
    std::cout << "    INFO: generic hit called, the MapObject at " << this << " shouldn't be a Player." << std::endl;
#endif
}

void MapObject::on_collision(MapObject &other) {
    // To retrieve from balavoine branch
    std::cout << "(!) WARN: generic on_collision called for MapObject at " << this << std::endl;
}

void MapObject::knockback(float di_x, float di_y){
    set_x(x + round(di_x));
    set_y(y + round(di_y));// To be changed later(knockback in the certain direction
}


bool MapObject::operator==(MapObject &other) {
#ifdef DEBUG_MODE
    std::cout << "    INFO: Called equality operator at " << this << " vs " << &other << std::endl;
#endif
    return ((*this <= other) | (other <= *this));
}

bool MapObject::operator<=(MapObject &other){
#ifdef DEBUG_MODE
    std::cout << "Equality operator at " << this << " vs " << &other << std::endl;
#endif
    int newpos_x = this->get_next_x();
    int newpos_y = this->get_next_y();
    int speed = this->get_speed();
    int othx = other.get_x();
    int othy = other.get_y();
    int othheight = other.get_height();
    int othwidth = other.get_width();
    // std::cout << "speed of " << this << " equals " << speed << std::endl;
    if (speed == 0) { //check is static to avoid dividing by 0
        // std::cout << "static collision: " << this << " and " << &other << std::endl;
        if (this->x >= other.get_x() && this->x <= other.get_x() + other.get_width()) {
            if (this->y >= other.get_y() && this->y <= other.get_y() + other.get_height()) {
                return true;
            }
        }
        if (this->x + this->width >= other.get_x() && this->x + this->width <= other.get_x() + other.get_width()) {
            if (this->y >= other.get_y() && this->y <= other.get_y() + other.get_height()) {
                return true;
            }
        }
        if (this->x >= other.get_x() && this->x <= other.get_x() + other.get_width()) {
            if (this->y + this->height >= other.get_y() && this->y + this->height <= other.get_y() + other.get_height()) {
                return true;
            }
        }
        if (this->x + this->width >= other.get_x() && this->x + this->width <= other.get_x() + other.get_width()) {
            if (this->y + this->height >= other.get_y() && this->y + this->height <= other.get_y() + other.get_height()) {
                return true;
            }
        }
		return false;
	}

	for (int k = speed; k > 1; k--) {
        int dxx = round(x + (newpos_x - x)/k);
		int dyy = round(y + (newpos_y - y)/k);
		if (dxx >= othx && dxx <= othx + othwidth) {
            if (dyy >= othy && dyy <= othy + othheight) {
                return true;
            }
        }
        if (dxx + this->width >= othx && dxx + this->width <= othx + othwidth) {
            if (dyy >= othy && dyy <= othy + othheight) {
                return true;
            }
        }
        if (dxx >= othx && dxx <= othx + othwidth) {
            if (dyy + this->height >= othy && dyy + this->height <= othy + othheight) {
                return true;
            }
        }
        if (dxx + this->width >= othx && dxx + this->width <= othx + othwidth) {
            if (dyy + this->height >= othy && dyy + this->height <= othy + othheight) {
                return true;
            }
        }
	    return false;
	}
    return false;
}

bool MapObject::get_drawsprite() const{
    return drawsprite;
}

void MapObject::draw(int camera_x, int camera_y) {
    //al_draw_filled_rectangle(x - camera_x, y - camera_y, x + width - camera_x, y + height - camera_y, al_map_rgb(255, 0, 0));
}

//void MapObject::preventhit(){
  //  garbage_collect = true;
//}

