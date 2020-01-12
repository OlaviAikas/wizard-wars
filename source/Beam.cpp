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

Beam::Beam(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool* mouse_down, Map* map)
: Spell( (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp),  (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp),  *dxp,  *dyp, width, height, noclip) {
    range = 4.5;
    this->pit = pit;
    this->map = map;
    this->origin_x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp);
    this->origin_y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp);
    this->dxp = dxp;
    this->dyp = dyp;
    this->mouse_down = mouse_down;
    bool hit = false;
    for (float i = 1; i <= range; i = i + 0.05) {
        this->x = round(x + (*dxp)*i*width);
        this->y = round(y + (*dyp)*i*height); 
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
    isBorS=true;
}

Beam::~Beam() { }

void Beam::move() {
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

std::string Beam::encode_spell(){
    std::string s="aaaaaaaaaaaaaaaaaaaaaaaaaaaaathisisspell;"+std::to_string(id)+";2;"+std::to_string(transmitted[1])+";"+std::to_string(transmitted[2])+";"+std::to_string(transmitted[3])+";"+std::to_string(transmitted[4])+";";
    s=s+element+";";
    s=s+std::to_string(origin_x)+";"+std::to_string(origin_y)+";"+std::to_string(*dxp)+";"+std::to_string(*dyp)+";"+std::to_string((*pit)->get_id())+";"+std::to_string(*mouse_down);
    return s;
 }

void Beam::draw(int camera_x, int camera_y) { 
    //ALLEGRO_SAMPLE* music00 = al_load_sample("music01.wav");
    //al_play_sample(music00, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // must_init(music01, "music01");
}
