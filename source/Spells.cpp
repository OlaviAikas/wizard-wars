#include "../headers/Spells.hpp"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>


Spell::Spell(int x, int y, float dir_x, float dir_y, int width, int height, bool noclip) : MapObject::MapObject(x, y, width, height, noclip) {
    this->dir_x = dir_x;
    this->dir_y = dir_y;
}

void Spell::draw(int camera_x, int camera_y) { std::cout << "hellods" << std::endl; };
void Spell::move() { std::cout << "helloms" << std::endl; };
