#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Projectile.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class FireP: public Projectile {
    public:
        FireP(int start_x, int start_y, float dir_x, float dir_y);
        ~FireP();

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    ALLEGRO_SAMPLE* music02;
};