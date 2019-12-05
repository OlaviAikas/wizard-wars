#pragma once

class Camera {
    public:
        Camera(int start_x, int start_y);

        int get_x();
        int get_y();

        void move_x(int d);
        void move_y(int d);

    private:
        int x;
        int y;
        char maxx;
        char maxy;
};