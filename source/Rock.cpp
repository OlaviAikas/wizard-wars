#include "../headers/Rock.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <allegro5/allegro.h>


Rock::Rock(int start_x, int start_y, float dir_x, float dir_y) 
            : Projectile::Projectile( start_x, start_y, dir_x, dir_y, 12, 12, false, 20) {
    damage = 10;
    sprite = al_load_bitmap("resources/rock_projectile.bmp");
    sound = al_load_sample("resources/rock.wav");
    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
}

Rock::~Rock() {
    al_destroy_bitmap(sprite);
    al_destroy_sample(sound);
}

int Rock::get_damage() {
    return damage;
}

// void must_init(bool, const char);

void Rock::draw(int camera_x, int camera_y) {
    if (!hit_animation) {
        al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);

        // must_init(al_init_primitives_addon(), "primitives");
        // must_init(al_init_image_addon(), "Image addon");
        // must_init(al_install_audio(), "Audio addon");
        // must_init(al_init_acodec_addon(), "Audio codecs addon");
        // must_init(al_reserve_samples(16), "reserve samples");
        
        
        // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
        // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
        
    } 
    else {
        // code for hit animation
        // please set this->garbage_collect to true when you're done
        al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
        this->garbage_collect = true;
    }
}
 

void Rock::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;
    }
}
