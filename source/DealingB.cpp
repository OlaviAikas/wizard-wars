#include "../headers/DealingB.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <allegro5/allegro_primitives.h>

DealingB::DealingB(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map) 
            : Beam::Beam(pit, dxp, dyp, 12, 12, false, mouse_down, map) {
    damage = 2;
    //sprite = al_load_bitmap("resources/HealB_Collision.bmp");

}
DealingB::~DealingB() { 

}

int DealingB::get_damage() {
    return damage;
}

void DealingB::draw(int camera_x, int camera_y) {
    
    al_draw_line(origin_x - camera_x, origin_y - camera_y, x - camera_x, y - camera_y, al_map_rgb(255, 0, 0), 8);
    //al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);

}
void DealingB::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
    }
}