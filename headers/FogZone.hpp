#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class FogZ: public Zone {
    public:
        FogZ(int start_x, int start_y);
        ~FogZ();

        int get_damage();

        virtual void on_collision(MapObject &other);
        virtual void draw(int camera_x, int camera_y);

    private:
        ALLEGRO_BITMAP* sprite;
        int damage;
        ALLEGRO_SAMPLE* music04;
};