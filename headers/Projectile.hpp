#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Projectile: public Spell {
    public:
        Projectile(int start_x, int start_y, int dir_x, int dir_y, bool noclip, int speed);
        void move();
};