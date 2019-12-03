#pragma once
#include "../headers/Rock.hpp"

Rock::Rock(int start_x, int start_y, int dir_x, int dir_y, bool noclip, int speed, int damage, ALLEGRO_BITMAP* sprite) : Projectile::Projectile(start_x, start_y, dir_x, dir_y, noclip, speed) {
    this->dest_x = start_x;
    this->dest_y = start_y;
}

int Rock::get_damage() {
    return damage;
}

void Rock::on_collision(MapObject other) {
    if (not other.get_noclip()) {
        dest_x = x;
        dest_y = y;
    }
