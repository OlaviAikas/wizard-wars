#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Shield.hpp"
#include "Spells.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>

class RockShield: public Shield {
    public:
        RockShield(int start_x, int start_y, float dir_x, float dir_y,bool subshield);
        ~RockShield();

        int get_damage();

        virtual void on_collision(MapObject &other);
        virtual void draw(int camera_x, int camera_y);
        
        std::list<std::list<int>> generate_subshield_coordinates();

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    bool subshield;
    ALLEGRO_SAMPLE* music11;
};