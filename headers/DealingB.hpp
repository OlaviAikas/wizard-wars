#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Beam.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>

class DealingB: public Beam {
    public:
        DealingB(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map);
        DealingB(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map, int IP, bool transmitted[5]);
        ~DealingB();

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    int maxdraw;
    int ticks;
};