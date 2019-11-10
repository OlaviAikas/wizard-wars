#pragma once

class MapObject {
    public:
        MapObject(int x, int y, int width, int height, bool noclip);
        void draw();
        void move();

        int get_x();
        int get_y();
        int get_width();
        int get_height();

    private:
        bool noclip;

        int x;
        int y;
        int width;
        int height;

};