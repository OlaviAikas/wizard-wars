#pragma once
#include "MapObject.hpp"

class Spell : public MapObject {
    public:
        Spell(int start_x, int start_y, int dir_x, int dir_y);
        virtual void draw(int camera_x, int camera_y);
        void set_target(int start_x, int start_y, int dir_x, int dir_y);

    private:
    int target_x;
    int target_y;
};
