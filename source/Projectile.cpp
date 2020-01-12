#include "../headers/Projectile.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>


Projectile::Projectile(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, int speed)
        : Spell(start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {
    this->speed = speed;
    this->subclass="projectile";
    // this->number = number;
    this->hit_animation = false;
}

// short Projectile::get_number() {
//     return this->number;
// }
Projectile::~Projectile() {};

void Projectile::move() {
    if (!hit_animation) {
        x = round(x + dir_x*speed);
        y = round(y + dir_y*speed);
    }
}

void Projectile::draw(int camera_x, int camera_y) {
    std::cout << "(!) WARN: Generic Projectile::draw called for Projectile at " << this << std::endl;
}

int Projectile::get_speed(){
	return this->speed;
}

int Projectile::get_next_x(){
	return round(x + dir_x*speed);
}

int Projectile::get_next_y(){
	return round(y + dir_y*speed);
}

std::string Projectile::encode_spell(){
    std::string s="aaaaaaaaaaaaaaaaaaaaaaaaaaaaathisisspell;"+std::to_string(id)+";0;"+std::to_string(transmitted[1])+";"+std::to_string(transmitted[2])+";"+std::to_string(transmitted[3])+";"+std::to_string(transmitted[4])+";";
    s=s+element+";";
    s=s+std::to_string(x)+";"+std::to_string(y)+";";
    s=s+std::to_string(dir_x)+";"+std::to_string(dir_y);
    return s;
    //id=1, from 2 to 5, transmitted, 6, type, 7, element, 8, x, 9, y, 10, dir_x, 11, dir_y
}