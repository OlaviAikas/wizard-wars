// use al_draw_soft_line?
#include "../headers/Beam.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <iostream>
#include <list>
#include "../headers/Player.hpp"

Beam::Beam(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool &mouse_down, Map* map)
: Spell( (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp),  (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp),  *dxp,  *dyp, width, height, noclip) {
    range = 3;
    this->pit = pit;
    this->map = map;
    this->origin_x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp);
    this->origin_y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp);
    this->dxp = dxp;
    this->dyp = dyp;
    this->mouse_down = mouse_down;
    bool hit = false;
    for (float i = 1; i <= range; i = i + 0.05) {
        // A loop that checks if it collides any player on the map
        for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {
            this->x = round(x + (*dxp)*i*width);
            this->y = round(y + (*dxp)*i*height);    
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
    //if (!mouse_down) {
    //    this->garbage_collect = true;
    //    std::cout << "killed beam" << std::endl;
    //}
    float dx = *dxp;
    float dy = *dyp;
    this->x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(dx);
    this->y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(dy);
    this->origin_x = x;
    this->origin_y = y;
    bool hit = false;
    for (float i = 1; i <= range; i = i + 0.05) {
        // A loop that checks if it collides any player on the map
        for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {
            this->x = round(x + (dx)*i*width);
            this->y = round(y + (dy)*i*height);    
            std::cout << dx << std::endl;
            std::cout << dx << std::endl;
            if (*this == **j) {
                hit = true;
                break;
            }
        }
    if (hit) { break; }
    }
}

void Beam::draw(int camera_x, int camera_y) { 
    ALLEGRO_SAMPLE* music00 = al_load_sample("music01.wav");
    al_play_sample(music00, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // must_init(music01, "music01");
}
