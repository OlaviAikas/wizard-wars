#include "../headers/Spray.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>

Spray::Spray(int start_x, int start_y, int width, int height, bool noclip)
        : Spell(start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {
    // this->number = number;
    this->hit_animation=false;
}

void Spray::draw(int camera_x, int camera_y) { }