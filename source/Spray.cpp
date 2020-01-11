#include "../headers/Spray.hpp"
#include "../headers/Spells.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <iostream>

Spray::Spray(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip)
        : Spell(start_x,  start_y,  dir_x,  dir_y, 30, 50, noclip) {
    // this->number = number;
    this->hit_animation=false;
};

// void must_init(bool, const char);

void Spray::draw(int camera_x, int camera_y) {
    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    ALLEGRO_SAMPLE* music20 = al_load_sample("resources/spray.wav");
    al_play_sample(music20, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    al_destroy_sample(music20);
 };