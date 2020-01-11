#include "../headers/Zone.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>

Zone::Zone(int start_x, int start_y, int width, int height, bool noclip)
        : Spell(start_x,  start_y,  0,  0, width, height, noclip) {
    // this->number = number;
    this->hit_animation=false;
}

void Zone::move() {}
void Zone::draw(int camera_x, int camera_y) { }
