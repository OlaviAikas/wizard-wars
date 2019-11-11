#pragma once
#include "MapObject.hpp"

class Player : public MapObject {
    public:
        Player(int start_x, int start_y);

        void move();

        void set_dest(int dest_x, int dest_y);

    private:
        int speed = 20;
        int dx;
        int dy;
        int dest_x;
        int dest_y;
};