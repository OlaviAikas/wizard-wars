#pragma once
#include "MapObject.hpp"
#include "Map.hpp"
#include "Spells.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>
#include "Map.hpp"
#include "Player.hpp"

class Spray: public Spell {
    public:
        Spray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool* mouse_down, Map* map);
        virtual ~Spray();
        virtual void draw(int camera_x, int camera_y);

        void move();

    protected:
        int ticks;
        bool hit_animation;
        ALLEGRO_SAMPLE* music20;
        float range;
        std::list<Player*>::iterator pit;
        int origin_x;
        int origin_y;
        float* dxp;
        float* dyp;
        bool* mouse_down;
        Map* map;
};