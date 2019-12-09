#pragma once
#include "MapObject.hpp"
#include <allegro5/allegro.h>
#include <list>

class Player : public MapObject {
    public:
        Player(int start_x, int start_y, int number, ALLEGRO_BITMAP*sprites[3]);

        void move();

        void on_collision(MapObject &other);

        void set_dest(int dest_x, int dest_y);

        short get_number();
        
        int get_hit_points();

        bool get_team();

        void draw(int camera_x, int camera_y);

        void onhit();

    private:
        short number;
        int speed;
        int old_x;
        int old_y;
        int dest_x;
        int dest_y;
        int hit_points;
        int lastgoodposx;
        int lastgoodposy;
        bool team;
        ALLEGRO_BITMAP*sprites[3];
        char count;
        char health;
        bool healthshow;
        bool damaged;
};
