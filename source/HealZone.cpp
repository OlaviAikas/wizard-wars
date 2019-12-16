#include "../headers/HealZone.hpp"
#include <iostream>
#include <math.h>
HealZ::HealZ(int start_x, int start_y) 
            : Zone::Zone(start_x, start_y, 200, 200, false) {
    damage = -10;
    sprite = al_load_bitmap("resources/zone.bmp");
}

int HealZ::get_damage() {
    return damage;
}

void HealZ::draw(int camera_x, int camera_y) {
   al_draw_scaled_bitmap(this->sprite, 0,0,64,64,x - camera_x, y - camera_y,width,height, 0);
}
