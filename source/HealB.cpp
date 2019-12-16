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
    int maxdraw = 1000;
    float vertex_x = x + dir_x * maxdraw - camera_x;
    float vertex_y = y + dir_y * maxdraw - camera_y;
    //if(HealB::get_noclip() == true){
        //vertex_x = player.get_x();
        //vertex_y = player.get_y();//deal with play thing 
    //};
    al_draw_line(x - camera_x, y - camera_y, vertex_x, vertex_y, al_map_rgb_f(0, 1, 1), 10);
}

void HealB::on_collision(MapObject &other) {
    
}