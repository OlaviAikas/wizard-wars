#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Projectile.hpp"
class Rock: public Projectile {
    public:
        Rock(int id, int start_x, int start_y, float dir_x, float dir_y);
        ~Rock();

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
};