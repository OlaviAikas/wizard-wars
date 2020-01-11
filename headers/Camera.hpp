#pragma once

class Camera {
    public:
        Camera(int start_x, int start_y);

        int get_x();
        int get_y();

        void move_x(int d);
        void move_y(int d);

        // void cameraUpdate(int *cameraPosition, int x, int y, int width, int height);
    private:
        int x;
        int y;
        int maxx;
        int maxy;

        // int screenWidth;
        // int screenHeight;
};
