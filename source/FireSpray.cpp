#include "../headers/Spray.hpp"
#include "../headers/FireSpray.hpp"
#include <iostream>
#include <math.h>

FireSpray::FireSpray(int start_x, int start_y, float dir_x, float dir_y) 
            : Spray::Spray(start_x, start_y, dir_x, dir_y, 100, 100, true) {
    damage = 20;
    sprite = al_load_bitmap("resources/firespray.bmp");
    ticks = 0; //Count time 
}

int FireSpray::get_damage() {
    return damage;
}

void FireSpray::draw(int camera_x, int camera_y) {
    float angle = atan2(dir_y,dir_x)+ALLEGRO_PI/8;
    al_draw_scaled_rotated_bitmap(this->sprite,0,0, x - camera_x, y - camera_y,4,2, angle,0);
    ticks += 3;
    if (ticks>50) {
        this->garbage_collect = true;
    };
}

void FireSpray::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;}
}