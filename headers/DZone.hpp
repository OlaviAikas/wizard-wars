#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"

class DamageZ: public Zone {
    public:
        DamageZ(int start_x, int start_y);
        DamageZ(int start_x, int start_y, int ID, bool transmitted[5]);
        ~DamageZ();

        int get_damage();

        virtual void on_collision(MapObject &other);
        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
};