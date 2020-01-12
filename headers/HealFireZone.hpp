#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class HealFireZ: public Zone {
    public:
        HealFireZ(int start_x, int start_y);
        HealFireZ(int start_x, int start_y, int ID, bool transmitted[5]);
        ~HealFireZ();
        int get_damage();

        virtual void on_collision(MapObject &other);
        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    ALLEGRO_SAMPLE* music12;
};