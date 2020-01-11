// use al_draw_soft_line?
#include "../headers/Beam.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include <allegro5/allegro5.h>
#include <math.h>
#include <iostream>
#include <list>

Beam::Beam(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, Map* &map)
: Spell( start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {
    lifetime = 2;
    range = 3;
    bool hit = false;
    for (float i = 1; i <= range; i = i + 0.05) {
        for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {
            this->x = round(x + dir_x*i*width);
            this->y = round(y + dir_y*i*height);    
            if (*this == **j) {
                hit = true;
                break;
            }
        }
    if (hit) { break; }
    }
}

Beam::~Beam() { }

void Beam::move() {
    lifetime--;
    if (lifetime <= 0) {
        garbage_collect = true;
    }
}

void Beam::draw(int camera_x, int camera_y) { }
