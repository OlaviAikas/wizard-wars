// use al_draw_soft_line?
#include "../headers/Beam.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>

Beam::Beam(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip)
: Spell( start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {

}

void Beam::draw(int camera_x, int camera_y) { };
