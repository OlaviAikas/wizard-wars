#include "../headers/Projectile.hpp"
#include "../headers/Spells.hpp"
#include <math.h>
#include <iostream>


Projectile::Projectile(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, int speed)
        : Spell( start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {
    this->speed = speed;
    // this->number = number;
}

// short Projectile::get_number() {
//     return this->number;
// }


void Projectile::move() {
    x = round(x + dir_x*speed);
    y = round(y + dir_y*speed);
}

void Projectile::draw(int camera_x, int camera_y) { };