#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class HealZ: public Zone {
    public:
        HealZ(int start_x, int start_y);
        HealZ(int start_x, int start_y, int ID, bool transmitted[5]);
        ~HealZ();
        int get_damage();

        virtual void on_collision(MapObject &other);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    ALLEGRO_SAMPLE* music14;
};