#pragma once
#include <allegro5/allegro5.h>
#include <cmath>



class MapObject {
    public:
        MapObject(int x, int y, int width, int height, bool noclip);
        virtual ~MapObject();
        virtual void draw(int camera_x, int camera_y);
        virtual void move();
        virtual void on_collision(MapObject &other);
        virtual void hit(const int amount);
        // I addded a knockback function for the special functions of spray
        virtual void knockback(float di_x, float di_y);
        //virtual void preventhit();

        int get_x() const;
        int get_y() const;
        void set_x(int x);
        void set_y(int y);
        int get_width() const;
        int get_height() const;
        bool get_noclip() const;
        bool get_garbage_collect() const;        
        bool operator==(MapObject &other);
        bool operator<=(MapObject &other);
        bool get_drawsprite() const;
        int get_next_x();
        int get_next_y();
        int get_speed();
        
    protected:
        bool noclip;
        bool havechanged;
        int x;
        int y;
        int width;
        int height;
        bool garbage_collect;
        bool drawsprite;
};
