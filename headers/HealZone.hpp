#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"

class HealZ: public Zone {
    public:
        HealZ(int start_x, int start_y);

        int get_damage();

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
};