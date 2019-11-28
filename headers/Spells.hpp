#pragma once
#include "MapObject.hpp"

class Spell : public MapObject {
    public:
        Spell(int x, int y, int width, int height, bool noclip, int damage, int healing, int target_x, int target_y);
        virtual void draw(int camera_x, int camera_y);
        int get_damage();
        int get_healing();
        virtual void on_collision(MapObject &other);
    protected:
        int damage;
        int healing;
        int target_x;
        int target_y;
};

class Arrow : protected Spell {
    public:
        virtual void draw(int camera_x, int camera_y);
};