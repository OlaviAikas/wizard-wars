#pragma once
#include "MapObject.hpp"
#include <allegro5/allegro.h>
#include <list>

class Player : public MapObject {
    public:
        Player(int start_x, int start_y, int number);

        void move();

        void on_collision(MapObject &other);

        void set_dest(int dest_x, int dest_y);

        short get_number();
        
        int get_hit_points();

        bool get_team();

        void draw(int camera_x, int camera_y);

        void onhit();

        int get_next_x();

        int get_next_y();

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
        int count;
        char health;
        bool healthshow;
        bool damaged;
        ALLEGRO_BITMAP* sprites1;
        ALLEGRO_BITMAP* sprites2;
        ALLEGRO_BITMAP* sprites3;
        ALLEGRO_BITMAP* sprites4;
        ALLEGRO_BITMAP* sprites5;
        ALLEGRO_BITMAP* sprites6;
        ALLEGRO_BITMAP* sprites7;
        ALLEGRO_BITMAP* sprites8;
        ALLEGRO_BITMAP* sprites9;
        ALLEGRO_BITMAP* sprites10;
        ALLEGRO_BITMAP* sprites0;
};
