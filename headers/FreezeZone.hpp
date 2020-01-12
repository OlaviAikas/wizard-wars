#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"
#include "Player.hpp"

class FreezeZ: public Zone {
    public:
        FreezeZ(int start_x, int start_y);
        ~FreezeZ();
        int get_damage();
        virtual void on_collision(Player &other);
        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
};