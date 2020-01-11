#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Zone: public Spell {
    public:
        Zone(int start_x, int start_y, int width, int height, bool noclip);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();
    protected:
        int time;
        bool hit_animation;
};