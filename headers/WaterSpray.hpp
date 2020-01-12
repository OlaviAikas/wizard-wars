//Water spray with special functions(knockback)
#pragma once
#include "Spray.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class WaterSpray: public Spray {
    public:
        WaterSpray(int start_x, int start_y, float dir_x, float dir_y);
        ~WaterSpray();

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    ALLEGRO_SAMPLE* music21;
};