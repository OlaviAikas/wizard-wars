#pragma once
#include "MapObject.hpp"
#include "Spells.hpp"

class Zone: public Spell {
    public:
        Zone(int start_x, int start_y, int width, int height, bool noclip);
        virtual ~Zone();
        virtual void draw(int camera_x, int camera_y);
        virtual void move();
        std::string encode_spell();
    protected:
        int time;
        bool hit_animation;
};