#include "../headers/FirePellet.hpp"
#include <iostream>
#include <math.h>

FireP::FireP(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 20, 20, false, 20) {
    damage = 20;
    sprite = al_load_bitmap("resources/fireProjectile.bmp");
}

int FireP::get_damage() {
    return damage;
}

void FireP::draw(int camera_x, int camera_y) {
    float at = atan2(dir_y,dir_x);
    al_draw_rotated_bitmap(this->sprite,0,0, x - camera_x, y - camera_y, at,0);
}

void FireP::on_collision(MapObject &other) { }