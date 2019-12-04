#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Projectile: public Spell {
    public:
        Projectile(int start_x, int start_y, int dir_x, int dir_y, bool noclip, int speed);
        void move();
        virtual void draw(int camera_x, int camera_y);

    protected:
    int speed;
};