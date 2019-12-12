#pragma once
#include "MapObject.hpp"

class Spell : public MapObject {
    public:
        Spell(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();

    protected:
    float dir_x;
    float dir_y;
    bool havechanged;

};