#include "../headers/MainShield.hpp"
#include <iostream>
#include <math.h>

MainShield::MainShield(int start_x, int start_y) 
            : Shield::Shield(start_x, start_y, 200, 200, false) {
    damage = 0;
    sprite = al_load_bitmap("resources/Shield.bmp");
}

int MainShield::get_damage() {
    return damage;
}

void MainShield::draw(int camera_x, int camera_y) {
    al_draw_scaled_bitmap(this->sprite, 0,0,64,64,x - camera_x, y - camera_y,width,height, 0);
}

void MainShield::move() { }
/*
void MainShield::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation) {
        other.get_garbage_collect();
    }
}
*/
void MainShield::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.get_garbage_collect();
        // Set garbage_collect to true iif other is not a Player?
        //this->hit_animation = true;
        //this->noclip = true;
    }
}