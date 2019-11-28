#pragma once
#include "MapObject.hpp"

class Spell : public MapObject {
    public:
        Spell(int x, int y, int width, int height, bool noclip, int damage, int healing);
        virtual void draw(int camera_x, int camera_y);
        int get_damage();
        int get_healing();
        virtual void on_collision(MapObject &other);
    protected:
        int damage;
        int healing;
};

// class Arrow : protected Spell {
//     public:
//         virtual void draw(int camera_x, int camera_y);
// };

class Projectile: public Spell {
    public:
        Projectile(int start_x, int start_y, int width, int height, bool noclip, int damage, int healing /*  , int number*/);

        void move();

        void on_collision(MapObject other);

        void set_target(int target_x, int target_y);

        // short get_number();

    private:
        // short number;
        int speed = 20;
        int old_x;
        int old_y;
        int dest_x;
        int dest_y;
        int target_x;
        int target_y;
        int hitpoint;
};
// continue with beam//