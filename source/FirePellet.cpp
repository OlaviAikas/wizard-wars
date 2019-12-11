#include "../headers/FirePellet.hpp"
#include <iostream>

FireP::FireP(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 20, 20, false, 20) {
    damage = 20;
    sprite = al_load_bitmap("resources/fireProjectiles.bmp");
}

int FireP::get_damage() {
    return damage;
}

void FireP::draw(int camera_x, int camera_y) {
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
}

void FireP::on_collision(MapObject other) { }