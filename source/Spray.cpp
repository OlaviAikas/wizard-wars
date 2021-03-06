#include "../headers/Spray.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Player.hpp"
#include "../headers/Map.hpp"
#include <math.h>
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <iostream>

Spray::Spray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool* mouse_down, Map* map)
: Spell( (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp),  (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp),  *dxp,  *dyp, width, height, noclip) {
    range = 2;
    this->pit = pit;
    this->map = map;
    this->origin_x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp);
    this->origin_y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp);
    this->dxp = dxp;
    this->dyp = dyp;
    this->mouse_down = mouse_down;
    bool hit = false;
}
Spray::~Spray() { }
void Spray::move() {
    if (!*mouse_down) {
        noclip = true;
        this->garbage_collect = true;
    }
    float dx = *dxp;
    float dy = *dyp;
    this->x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(dx);
    this->y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(dy);
    this->origin_x = x;
    this->origin_y = y;
    bool hit = false;
    for (float i = 1; i <= range; i = i + 0.05) {
        this->x = round(x + (dx)*i*width);
        this->y = round(y + (dy)*i*height); 
        // A loop that checks if it collides any player on the map
        for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {   
            if (*this == **j) {
                hit = true;
                break;
            }
        }
        if (hit) { break; }
        for (std::list<MapObject*>::iterator j = map->statics.begin(); j != map->statics.end(); j++) {
            if (*this == **j) {
                hit = true;
                break;
            }
        }
    if (hit) { break; }
    }
}

void Spray::draw(int camera_x, int camera_y){ }
