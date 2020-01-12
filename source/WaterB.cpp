#include "../headers/WaterB.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <allegro5/allegro_primitives.h>

WaterB::WaterB(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map) 
            : Beam::Beam(pit, dxp, dyp, 12, 12, false, mouse_down, map) {
    damage = 1;

}
WaterB::~WaterB() {}
int WaterB::get_damage() {
    return damage;
}

void WaterB::draw(int camera_x, int camera_y) {
    al_draw_line(origin_x - camera_x, origin_y - camera_y, x - camera_x, y - camera_y, al_map_rgb(0, 0, 200), 8);
}
void WaterB::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
    }
}