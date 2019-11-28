// Original Wanqi's file

#pragma once
#include "MapObject.hpp"
#include <list>

class Spell : public MapObject {
    public:
        Spell(int x, int y, int width, int height, bool noclip, int damage, int heal);
        void draw(int camera_x, int camera_y);
        int get_damage();
        int get_heal();
    protected:
        int damage;
        int healing;
};

class Projectile: public MapObject {
    public:
        Projectile(int start_x, int start_y, int number);

        void move();

        void on_collision(MapObject other);

        void set_target(int target_x, int target_y);

        void set_dest(int dest_x, int dest_y);

        short get_number();

    private:
        short number;
        int speed = 20;
        int old_x;
        int old_y;
        int target_x;
        int target_y;
        int hitpoint;
        int dest_x;
        int dest_y;
};
// continue with beam//

