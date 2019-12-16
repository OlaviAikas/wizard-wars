#include "../headers/HealZone.hpp"
#include <iostream>
#include <math.h>
HealZ::HealZ(int start_x, int start_y) 
            : Zone::Zone(start_x, start_y, 100, 100, false) {
    damage = -10;
    sprite = al_load_bitmap("resources/zone.bmp");
}

int HealZ::get_damage() {
    return damage;
}

void HealZ::draw(int camera_x, int camera_y) {
   al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
}

void HealZ::on_collision(MapObject &other) { }