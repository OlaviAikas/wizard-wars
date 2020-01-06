#include "../headers/HealP.hpp"
#include <iostream>

HealP::HealP(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 12, 12, false, 20) {
    damage = -10;
    sprite = al_load_bitmap("resources/healProjectile.bmp");
}

int HealP::get_damage() {
    return damage;
}

void HealP::draw(int camera_x, int camera_y) {
    // Put this code under if (!hit_animation) if hit animation is required
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
}

void HealP::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;
        this->garbage_collect = true; // remove this line if a hit animation needs to be played
    }
}
