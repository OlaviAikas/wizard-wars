#include "../headers/HealB.hpp"
#include <iostream>
#include <math.h>

HealB::HealB(int start_x, int start_y, float dir_x, float dir_y) 
            : Beam::Beam(start_x, start_y, dir_x, dir_y, 2, 50, false) {
    damage = -10;
    sprite = al_load_bitmap("resources/HealB.bmp");
    //ticks = 0; //remove later
}

int HealB::get_damage() {
    return damage;
}

void HealB::draw(int camera_x, int camera_y) {
    int maxdraw = 500;
    float vertex_x = x + dir_x * maxdraw - camera_x;
    float vertex_y = y + dir_y * maxdraw - camera_y;
    //if(HealB::get_noclip() == true){
        //vertex_x = player.get_x();
        //vertex_y = player.get_y();//deal with play thing 
    //};
    float angle = atan(dir_y/dir_x);
    //std::cout << x << y << std::endl;
    al_draw_scaled_rotated_bitmap(this->sprite, 0, 0, x-camera_x, y-camera_y, maxdraw, 3, angle, 0);
}

void HealB::on_collision(MapObject &other) {
}