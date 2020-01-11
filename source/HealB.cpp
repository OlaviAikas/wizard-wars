#include "../headers/HealB.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <allegro5/allegro_primitives.h>

HealB::HealB(int start_x, int start_y, float dir_x, float dir_y, Map* &map) 
            : Beam::Beam(start_x, start_y, dir_x, dir_y, 12, 12, false, map) {
    damage = -10;
    sprite = al_load_bitmap("resources/HealB.bmp");
    maxdraw = 50;
}
HealB::~HealB() { };

int HealB::get_damage() {
    return damage;
}

// bugs to be fixed: move() virtual?


// void must_init(bool, const char);

void HealB::draw(int camera_x, int camera_y) {
    // float angle = atan2(dir_y,dir_x) - ALLEGRO_PI/30;
    // if(HealB::get_noclip() == false){
    //     ticks++;
    //     height *= ticks;
    //     al_draw_scaled_rotated_bitmap(this->sprite, 0, 0, x-camera_x, y-camera_y, ticks, 3, angle, 0);
    // }else{
    //     sprite = al_load_bitmap("resources/HealB_Collision.bmp");
    //     al_draw_scaled_rotated_bitmap(this->sprite, 0, 0, x-camera_x, y-camera_y, ticks, 3, angle, 0);
    //     //still can't check collision thing
    //     this->garbage_collect = true;
    // }
    // if (ticks>100) {
    //     this->garbage_collect = true;
    // };

    al_draw_filled_rectangle(x - camera_x, y - camera_y, x - camera_x + width, y - camera_y + height, al_map_rgb(0, 255, 0));
    // ALLEGRO_SAMPLE* music06 = al_load_sample("resources/music06.wav");
    // al_play_sample(music06, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    // al_destroy_sample(music06);
}

void HealB::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
        maxdraw = sqrt((other.get_x()-x)* (other.get_x()-x)+ (other.get_y()-y)*(other.get_y()-y));
    }
}



