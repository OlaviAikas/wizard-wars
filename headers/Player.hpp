#pragma once
#include "MapObject.hpp"

class Player : public MapObject {
    public:
        Player(int start_x, int start_y, int number, ALLEGRO_BITMAP*[2] sprites);

        void move();

        void set_dest(int dest_x, int dest_y);

        short get_number();s

				void draw(int camera_x, int camera_y);

				int count;

				void update_tick;

				void onhit;

    private:
        short team;
        int speed = 20;
        int dx;
        int dy;
        int dest_x;
        int dest_y;
				ALLEGRO_BITMAP* sprites;
				char health;
				bool healthshow;
				bool damaged;

};
