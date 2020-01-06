#pragma once
#include "MapObject.hpp"

class Spell : public MapObject {
    public:
        Spell(int id, int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();

    float get_dir_x();
    float get_dir_y();
    int get_id();

    bool get_havechanged();
    void reset_havechanged();
    protected:
    int id;
    float dir_x;
    float dir_y;
    bool havechanged;

};