#include "../headers/Shield.hpp"
#include <math.h>
#include <iostream>

Shield::Shield(int start_x, int start_y, int width, int height, bool noclip)
        : Spell(start_x,  start_y,  0,  0, width, height, noclip) {
    this->hit_animation=false;
    
}

void Shield::draw(int camera_x, int camera_y) { }