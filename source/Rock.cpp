#include "../headers/Rock.hpp"
#include <iostream>

Rock::Rock(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 12, 12, false, 20) {
    damage = 10;
    sprite = al_load_bitmap("resources/rock_projectile.bmp");
}

int Rock::get_damage() {
    return damage;
}

void Rock::draw(int camera_x, int camera_y) {
    if (!hit_animation) {
        al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
    } else {
        // code for hit animation
        // please set this->garbage_collect to true when you're done
    }
}

void Rock::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
    }
}
