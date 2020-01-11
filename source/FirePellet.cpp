#include "../headers/FirePellet.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>

FireP::FireP(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, 20, 20, false, 20) {
    damage = 20;
    sprite = al_load_bitmap("resources/fireProjectile.bmp");
    element = "1";
}

int FireP::get_damage() {
    return damage;
}

// void must_init(bool, const char);

void FireP::draw(int camera_x, int camera_y) {
    // Put this code under if (!hit_animation) if hit animation is required
    float at = atan2(dir_y,dir_x);
    al_draw_rotated_bitmap(this->sprite,0,0, x - camera_x, y - camera_y, at,0);

    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    ALLEGRO_SAMPLE* music02 = al_load_sample("resources/fire_pellet.wav");
    al_play_sample(music02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    al_destroy_sample(music02);
}

void FireP::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;
        this->garbage_collect = true; // remove this line if a hit animation needs to be played
    }
}