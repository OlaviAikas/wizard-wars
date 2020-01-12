#include "../headers/HealP.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>

HealP::HealP(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 12, 12, false, 20) {
    damage = -10;
    sprite = al_load_bitmap("resources/healProjectile.bmp");
    element = "3";
}

HealP::HealP(int start_x, int start_y, float dir_x, float dir_y, int ID, bool transmitted[5]) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 12, 12, false, 20) {
    damage = -10;
    sprite = al_load_bitmap("resources/healProjectile.bmp");
    element = "3";
    id=ID;
    for(int i=0; i<5; i++){        
        this->transmitted[i]=transmitted[i];
    }
    music13 = al_load_sample("resources/heal_projectile.wav");
    if (music13) al_play_sample(music13, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id);
}

HealP::~HealP(){
    al_destroy_bitmap(sprite);
    al_destroy_sample(music13);
}

int HealP::get_damage() {
    return damage;
}



void HealP::draw(int camera_x, int camera_y) {
    // Put this code under if (!hit_animation) if hit animation is required
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);

    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    // ALLEGRO_SAMPLE* music08 = al_load_sample("resources/music08.wav");
    // al_play_sample(music08, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    // al_destroy_sample(music08);
}

void HealP::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;
        this->garbage_collect = true; // remove this line if a hit animation needs to be played
    }
}
