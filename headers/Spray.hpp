#pragma once
#include "MapObject.hpp"
#include "Map.hpp"
#include "Spells.hpp"

class Spray: public Spell {
    public:
        Spray(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip,  Map* &map);
        virtual void draw(int camera_x, int camera_y);

    protected:
        int ticks;
        bool hit_animation;
};