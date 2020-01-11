#include "../headers/HealB.hpp"
#include <iostream>
#include <math.h>
#include <allegro5/allegro_primitives.h>

HealB::HealB(int start_x, int start_y, float dir_x, float dir_y, Map* &map) 
            : Beam::Beam(start_x, start_y, dir_x, dir_y, 12, 12, false, map) {
    damage = -10;
    sprite = al_load_bitmap("resources/HealB.bmp");
    maxdraw = 50;
}
HealB::~HealB() { };

int HealB::get_damage() {
    return damage;
}

// bugs to be fixed: move() virtual?

void HealB::draw(int camera_x, int camera_y) {
    al_draw_filled_rectangle(x - camera_x, y - camera_y, x - camera_x + width, y - camera_y + height, al_map_rgb(0, 255, 0));
}

void HealB::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
        maxdraw = sqrt((other.get_x()-x)* (other.get_x()-x)+ (other.get_y()-y)*(other.get_y()-y));
    }
}



