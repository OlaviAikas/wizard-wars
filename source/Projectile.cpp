#include "../headers/Projectile.hpp"
#include "../headers/Spells.hpp"
#include <math.h>


Projectile::Projectile(int start_x, int start_y, int dir_x, int dir_y, bool noclip, int speed)
        : Spell( start_x,  start_y,  dir_x,  dir_y, noclip) {
    this->speed = speed;
    // this->number = number;
}

// short Projectile::get_number() {
//     return this->number;
// }


void Projectile::move() {
    x = x + dir_x*speed;
    y = y + dir_y*speed;
};

void Projectile::draw(int camera_x, int camera_y) { };
