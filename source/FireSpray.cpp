#include "../headers/Spray.hpp"
#include "../headers/FireSpray.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <list>
#include "../headers/Player.hpp"
#include "../headers/Map.hpp"


FireSpray::FireSpray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map) 
            : Spray::Spray(pit, dxp, dyp, 12, 12, false, mouse_down, map) {
    damage = 20;
    sprite = al_load_bitmap("resources/firespray.bmp");
    ticks = 0; //Count time 
    // music03 = al_load_sample("resources/fire_spray.wav");
    // if (music03) al_play_sample(music03, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
}

FireSpray::~FireSpray() {
    al_destroy_bitmap(sprite);
}
int FireSpray::get_damage() {
    return damage;
}

// void must_init(bool, const char);

void FireSpray::draw(int camera_x, int camera_y) {
    float angle = atan2(dir_y,dir_x)+ALLEGRO_PI/8;
    al_draw_scaled_rotated_bitmap(this->sprite,0,0, x - camera_x, y - camera_y,4,2, angle,0);
    ticks += 3;
    if (ticks>50) {
        this->garbage_collect = true;
    };

    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    //ALLEGRO_SAMPLE* music03 = al_load_sample("resources/fire_spray.wav");
    //al_play_sample(music03, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    //al_destroy_sample(music03);
}

void FireSpray::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;}
}