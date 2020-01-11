#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Shield: public Spell {
    public:
        Shield(int start_x, int start_y, int width, int height, bool noclip);
        virtual void draw(int camera_x, int camera_y);

    protected:
        bool hit_animation;
};
