#include "../headers/HealB.hpp"
#include <iostream>
#include <math.h>

HealB::HealB(int start_x, int start_y, float dir_x, float dir_y) 
            : Beam::Beam(start_x, start_y, dir_x, dir_y, 2, 2, false) {
    damage = -10;
    sprite = al_load_bitmap("resources/HealB.bmp");
    maxdraw = 500;
    //ticks = 0; //remove later
}

int HealB::get_damage() {
    return damage;
}

// bugs to be fixed: move() virtual?

void HealB::draw(int camera_x, int camera_y) {
    //int maxdraw = 500;
    float vertex_x = x + dir_x * maxdraw - camera_x;
    float vertex_y = y + dir_y * maxdraw - camera_y;
    if(HealB::get_noclip() == true){
        sprite = al_load_bitmap("resources/HealB_Collision.bmp");
      //  vertex_x = other.get_x();
        //vertex_y = player.get_y();//deal with play thing 
    }
    float angle = atan2(dir_y,dir_x); 
    al_draw_scaled_rotated_bitmap(this->sprite, 0, 0, x-camera_x, y-camera_y, maxdraw, 3, angle, 0);
}

void HealB::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
        maxdraw = sqrt((other.get_x()-x)* (other.get_x()-x)+ (other.get_y()-y)*(other.get_y()-y));
    }
}



