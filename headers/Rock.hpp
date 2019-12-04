#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Projectile.hpp"
class Rock: public Projectile {
    public:
        Rock(int start_x, int start_y, int dir_x, int dir_y);

        int get_damage();

        void on_collision(MapObject other);

        void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int x;
    int y;
    int damage;
};