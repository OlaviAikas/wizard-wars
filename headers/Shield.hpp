#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Shield: public Spell {
    public:
        Shield(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, bool subshield);
        ~Shield();
        virtual void draw(int camera_x, int camera_y);

    protected:
        bool hit_animation;
        bool subshield;
        int time1;
};
