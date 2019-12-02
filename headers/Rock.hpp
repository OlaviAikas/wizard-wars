#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Projectile.hpp"
class Rock: public Projectile {
    public:
        Rock(int start_x, int start_y, int width, int height, bool noclip, int damage, ALLEGRO_BITMAP* sprite);

        void on_collision(MapObject other);

        void draw(ALLEGRO_BITMAP* sprite);
};