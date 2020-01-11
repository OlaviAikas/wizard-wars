#include "../headers/HealB.hpp"
#include <iostream>
#include <math.h>

HealB::HealB(int start_x, int start_y, float dir_x, float dir_y) 
            : Beam::Beam(start_x, start_y, dir_x, dir_y, 2, 2, false) {
    damage = -10;
    sprite = al_load_bitmap("resources/HealB.bmp");
    maxdraw = 50;
    ticks = 0; // count time and scan check
}

int HealB::get_damage() {
    return damage;
}

// bugs to be fixed: move() virtual?

void HealB::draw(int camera_x, int camera_y) {
    float angle = atan2(dir_y,dir_x) - ALLEGRO_PI/30;
    if(HealB::get_noclip() == false){
        ticks++;
        height *= ticks;
        al_draw_scaled_rotated_bitmap(this->sprite, 0, 10, x-camera_x, y-camera_y, ticks, 3, angle, 0);
    }else{
        sprite = al_load_bitmap("resources/HealB_Collision.bmp");
        al_draw_scaled_rotated_bitmap(this->sprite, 0, 10, x-camera_x, y-camera_y, ticks, 3, angle, 0);
        //still can't check collision thing
        this->garbage_collect = true;
    }
    if (ticks>100) {
        this->garbage_collect = true;
    };
}

void HealB::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
        maxdraw = sqrt((other.get_x()-x)* (other.get_x()-x)+ (other.get_y()-y)*(other.get_y()-y));
    }
}



