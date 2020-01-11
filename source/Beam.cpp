// use al_draw_soft_line?
#include "../headers/Beam.hpp"
#include "../headers/Spells.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <iostream>

Beam::Beam(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip)
: Spell( start_x,  start_y,  dir_x,  dir_y, width, height, noclip) {

}

void Beam::draw(int camera_x, int camera_y) { 
    ALLEGRO_SAMPLE* music00 = al_load_sample("music01.wav");
    al_play_sample(music00, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // must_init(music01, "music01");
}
