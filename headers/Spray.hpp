#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Spray: public Spell {
    public:
        Spray(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip);
        ~Spray();

        virtual void draw(int camera_x, int camera_y);

    protected:
        int ticks;
        bool hit_animation;
        ALLEGRO_SAMPLE* music20;
};