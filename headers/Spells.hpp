#pragma once
#include "MapObject.hpp"

class Spell : public MapObject {
    public:
        Spell(int start_x, int start_y, int dir_x, int dir_y, bool noclip);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();

    protected:
    int dir_x;
    int dir_y;
};
