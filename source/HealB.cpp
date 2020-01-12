#include "../headers/HealB.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <allegro5/allegro_primitives.h>

HealB::HealB(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map) 
            : Beam::Beam(pit, dxp, dyp, 12, 12, false, mouse_down, map) {
    damage = -2;
    sprite = al_load_bitmap("resources/HealB.bmp");
    //maxdraw = 0;
    //ticks = 0;

}
HealB::~HealB() { };

int HealB::get_damage() {
    return damage;
}

// bugs to be fixed: move() virtual?


// void must_init(bool, const char);

void HealB::draw(int camera_x, int camera_y) {
    //float angle = atan2(origin_y-y,origin_x-x);
    //maxdraw = sqrt((origin_x-x)* (origin_x-x)+ (origin_y-y)* (origin_y-y));
    //al_draw_scaled_rotated_bitmap(this->sprite, 0, 0, origin_x-camera_x, origin_y-camera_y, maxdraw, 3, angle-ALLEGRO_PI, 0);
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

    al_draw_line(origin_x - camera_x, origin_y - camera_y, x - camera_x, y - camera_y, al_map_rgb(0, 255, 0), 2);
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



