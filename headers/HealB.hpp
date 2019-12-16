#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Beam.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

class HealB: public Beam {
    public:
        HealB(int start_x, int start_y, float dir_x, float dir_y);

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
    
};