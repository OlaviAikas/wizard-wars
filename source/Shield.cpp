#include "../headers/Shield.hpp"
#include <math.h>
#include <iostream>

Shield::Shield(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, bool subshield)
        : Spell(start_x,  start_y,  0,  0, width, height, noclip) {
    this->hit_animation=false;
    this->subshield=subshield;
}
Shield::~Shield() { };

void Shield::draw(int camera_x, int camera_y) { }