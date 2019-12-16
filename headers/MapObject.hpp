#pragma once
#include <allegro5/allegro5.h>


class MapObject {
    public:
        MapObject(int x, int y, int width, int height, bool noclip);
        virtual void draw(int camera_x, int camera_y);
        virtual void move();
        virtual void on_collision(MapObject &other);
        virtual void hit(const int amount);

        int get_x() const;
        int get_y() const;
        int get_width() const;
        int get_height() const;
        bool get_noclip() const;
        bool get_garbage_collect() const;        
        bool operator==(const MapObject &other) const;
        bool operator<=(const MapObject &other) const;

    protected:
        bool noclip;
        int x;
        int y;
        int width;
        int height;
        bool garbage_collect;
};
