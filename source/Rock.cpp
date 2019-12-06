#include "../headers/Rock.hpp"
#include <iostream>

Rock::Rock(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 12, 12, false, 20) {
    damage = 10;
    sprite = al_load_bitmap("resources/projectile.bmp");
}

int Rock::get_damage() {
    return damage;
}

void Rock::draw(int camera_x, int camera_y) {
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
}

void Rock::on_collision(MapObject other) { }
