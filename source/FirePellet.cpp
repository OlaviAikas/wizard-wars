#include "../headers/FirePellet.hpp"
#include <iostream>
#include <math.h>

FireP::FireP(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 20, 20, false, 20) {
    damage = 20;
    sprite = al_load_bitmap("resources/fireProjectile.bmp");
    element = "1";
}

int FireP::get_damage() {
    return damage;
}

void FireP::draw(int camera_x, int camera_y) {
    // Put this code under if (!hit_animation) if hit animation is required
    float at = atan2(dir_y,dir_x);
    al_draw_rotated_bitmap(this->sprite,0,0, x - camera_x, y - camera_y, at,0);
}

void FireP::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;
        this->garbage_collect = true; // remove this line if a hit animation needs to be played
    }
}