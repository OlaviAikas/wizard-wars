#include "../headers/HealZone.hpp"
#include <iostream>
#include <math.h>
HealZ::HealZ(int start_x, int start_y) 
            : Zone::Zone(start_x, start_y, 200, 200, true) {
    damage = -1;
    sprite = al_load_bitmap("resources/healingzone.bmp");
    time = 0;
}

int HealZ::get_damage() {
    return damage;
}

void HealZ::draw(int camera_x, int camera_y) {
    al_draw_tinted_scaled_bitmap(this->sprite, al_map_rgba_f(1, 1, 1, -0.5),0,0,64,64,x - camera_x, y - camera_y,width,height, 0);
    //how to count ticks?
    time=time+1;
    if (time>100) {
        this->garbage_collect = true;
    };
    //al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
   
}

void HealZ::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation) {
        other.hit(this->get_damage());
    }
 }

void HealZ::move() { /* A zone does not move */ }
