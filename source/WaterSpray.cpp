#include "../headers/Spray.hpp"
#include "../headers/WaterSpray.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>



WaterSpray::WaterSpray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map) 
            : Spray::Spray(pit, dxp, dyp, 12, 12, false, mouse_down, map) {
    damage = 20;
    sprite = al_load_bitmap("resources/waveSpray.bmp");
    ticks = 0; //Count time
    // music21 = al_load_sample("resources/water_spray.wav");
    // if (music21) al_play_sample(music21, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
}


WaterSpray::~WaterSpray() {
    al_destroy_bitmap(sprite);
}

int WaterSpray::get_damage() {
    return damage;
}

// void must_init(bool, const char);

void WaterSpray::draw(int camera_x, int camera_y) {
    //typedef struct ALLEGRO_MOUSE_STATE ALLEGRO_MOUSE_STATE;
    //ALLEGRO_MOUSE_STATE state;
    //al_get_mouse_state(&state);
    //float angle = atan2(state.y - y,state.x-x);//-pi/10
    //int bitmapw = al_get_bitmap_width(sprite);
    //int bitmaph = al_get_bitmap_height(sprite);
    //al_draw_scaled_rotated_bitmap(this->sprite,0,bitmaph/2, x -camera_x, y - camera_y,4,2, angle,0);
    //ticks += 3;
    //if (ticks>100) {
    //    this->garbage_collect = true;
    //};

    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    //ALLEGRO_SAMPLE* music21 = al_load_sample("resources/water_spray.wav");
    //al_play_sample(music21, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_LEGRO_SAMPLE* music20;font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    //al_destroy_sample(music21);

    al_draw_line(origin_x - camera_x, origin_y - camera_y, x - camera_x, y - camera_y, al_map_rgb(0,0,255), 3);
}

void WaterSpray::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        other.knockback(300*dir_x,300*dir_y);
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;
    }
}