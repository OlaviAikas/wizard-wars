#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Zone.hpp"
#include "Player.hpp"

class FreezeZ: public Zone {
    public:
        FreezeZ(int start_x, int start_y);
        FreezeZ(int start_x, int start_y, int ID, bool transmitted[5]);
        ~FreezeZ();
        int get_damage();
        using MapObject::on_collision;
        virtual void on_collision(Player &other);
        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
};