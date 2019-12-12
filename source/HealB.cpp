#include "../headers/HealB.hpp"
#include <iostream>

HealB::HealB(int start_x, int start_y, float dir_x, float dir_y) 
            : Beam::Beam(start_x, start_y, dir_x, dir_y, 2, 50, false) {
    damage = -10;
    sprite = al_load_bitmap("resources/HealB.bmp");
}

int HealB::get_damage() {
    return damage;
}

void HealB::draw(int camera_x, int camera_y) {
    //al_draw_line(float x1, float y1, float x2, float y2,
   //ALLEGRO_COLOR color, float thickness)
    
}

void HealB::on_collision(MapObject &other) { }