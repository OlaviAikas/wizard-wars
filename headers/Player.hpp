#pragma once
#include "MapObject.hpp"

class Player : public MapObject {
    public:
        Player(int start_x, int start_y, int number);

        void move();

        void on_collision(MapObject other);

        void set_dest(int dest_x, int dest_y);

        short get_number();

    private:
        short number;
        int speed = 20;
        int dx;
        int dy;
        int dest_x;
        int dest_y;
};