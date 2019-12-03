#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Projectile.hpp"
class Rock: public Projectile {
    public:
        Rock(int start_x, int start_y, int dir_x, int dir_y, bool noclip, int speed, int damage, ALLEGRO_BITMAP* sprite);

        int get_damage();

        void on_collision(MapObject other);

        void draw(ALLEGRO_BITMAP* sprite);

    private:
    ALLEGRO_BITMAP* sprite = al_load_bitmap("resources/Projectile.bmp");
    int dest_x;
    int dest_y;
    int damage;
    int speed;
};