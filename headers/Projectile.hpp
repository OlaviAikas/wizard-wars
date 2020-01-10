#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Projectile: public Spell {
    public:
        Projectile(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, int speed);
        virtual void move();
        virtual void draw(int camera_x, int camera_y);
        int get_speed();
        int get_next_x();
        int get_next_y();

    protected:
        int speed;
        bool hit_animation; // Prevents movement and runs the animation
};