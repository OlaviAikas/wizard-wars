#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Shield.hpp"
#include "Spells.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class MainShield: public Shield {
    public:
        MainShield(int start_x, int start_y);
        ~MainShield();

        int get_damage();

        virtual void on_collision(MapObject &other);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    ALLEGRO_SAMPLE* music11;
};