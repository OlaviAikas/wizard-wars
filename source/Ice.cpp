#include "../headers/Ice.hpp"
#include <iostream>
Ice::Ice(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 12, 12, false, 40) {
    damage = 5;
    sprite = al_load_bitmap("resources/iceProjectiles.bmp");
}

int Ice::get_damage() {
    return damage;
}

void Ice::draw(int camera_x, int camera_y) {
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
}

void Ice::on_collision(MapObject other) { }
