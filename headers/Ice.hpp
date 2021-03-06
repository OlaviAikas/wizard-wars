#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Projectile.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Ice: public Projectile {
    public:
        Ice(int start_x, int start_y, float dir_x, float dir_y);
        Ice(int start_x, int start_y, float dir_x, float dir_y, int IP, bool transmitted[5]);
        ~Ice();

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    ALLEGRO_SAMPLE* music10;
};