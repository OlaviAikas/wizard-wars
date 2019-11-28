#pragma once
#include <allegro5/allegro5.h>

class MapObject {
    public:
        MapObject(int x, int y, int width, int height, bool noclip, ALLEGRO_BITMAP* sprite);
        virtual void draw(int camera_x, int camera_y);
        void move();
        virtual void on_collision(MapObject &other);

        int get_x();
        int get_y();
        int get_width();
        int get_height();
        bool get_noclip();
        
        bool operator==(MapObject other);

    protected:
        bool noclip;
        
        int x;
        int y;
        int width;
        int height;

        ALLEGRO_BITMAP* sprite;
        bool has_sprite;
};
