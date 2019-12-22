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

        int get_x();
        int get_y();    
        int get_dest_x();
        int get_dest_y();
        void change_x(int x);
        void change_y(int y);
        void change_destx(int destx);
        void change_desty(int desty);
    
        bool get_havechanged();
        void reset_havechanged();

        void draw(int camera_x, int camera_y);

    private:
        short number;
        int speed = 15;
        int old_x;
        int old_y;
        int dest_x;
        int dest_y;
        int hit_points;
        int lastgoodposx;
        int lastgoodposy;
        bool havechanged;
        bool team;
        int game_state;
        ALLEGRO_BITMAP* sprite;
};
