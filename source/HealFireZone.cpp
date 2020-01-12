#include "../headers/HealFireZone.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>

HealFireZ::HealFireZ(int start_x, int start_y) 
            : Zone::Zone(start_x, start_y, 200, 200, true) {
    damage = -2;
    sprite = al_load_bitmap("resources/HealFireZ.bmp");
    time = 0;
    element="4";
}

HealFireZ::HealFireZ(int start_x, int start_y, int ID, bool transmitted[5]) 
            : Zone::Zone(start_x, start_y, 200, 200, true) {
    damage = -2;
    sprite = al_load_bitmap("resources/HealFireZ.bmp");
    time = 0;
    element="4";
    id=ID;
    for(int i=0; i<5; i++){        
        this->transmitted[i]=transmitted[i];
    }
}

int HealFireZ::get_damage() {
    return damage;
}

HealFireZ::~HealFireZ() {
    al_destroy_bitmap(sprite);
}

void HealFireZ::draw(int camera_x, int camera_y) {
    al_draw_scaled_bitmap(this->sprite, 0,0,64,64,x - camera_x, y - camera_y,width,height, 0);
    //how to count ticks?
    time=time+1;
    if (time>100) {
        this->garbage_collect = true;

    };
    //al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);

    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    // ALLEGRO_SAMPLE* music07 = al_load_sample("resources/music07.wav");
    // al_play_sample(music07, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    // al_destroy_sample(music07);
}

void HealFireZ::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation) {
        other.hit(this->get_damage());
    }
 }