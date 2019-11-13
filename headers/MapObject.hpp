#pragma once

class MapObject {
    public:
        MapObject(int x, int y, int width, int height, bool noclip);
        void draw(int camera_x, int camera_y);
        void move();

        int get_x();
        int get_y();
        int get_width();
        int get_height();

        bool operator==(MapObject other);

    protected:
        bool noclip;

        int x;
        int y;
        int width;
        int height;

};