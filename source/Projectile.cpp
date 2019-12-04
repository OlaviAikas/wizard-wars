#include "../headers/Projectile.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>


Projectile::Projectile(int start_x, int start_y, int dir_x, int dir_y, int width, int height, bool noclip, int speed)
        : Spell( start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {
    this->speed = speed;
    // this->number = number;
}

// short Projectile::get_number() {
//     return this->number;
// }


void Projectile::move() {
    x = x + dir_x*speed;
    y = y + dir_y*speed;
    std::cout << "x in move: " << x << std::endl;
}

void Projectile::draw(int camera_x, int camera_y) { };
