#pragma once
#include "MapObject.hpp"
#include <allegro5/allegro.h>
#include <list>
#include <string>

class Player : public MapObject {
    public:
        Player(int start_x, int start_y, short number,int team);
        ~Player();

        void move();

        virtual void on_collision(MapObject &other);

        void set_dest(int dest_x, int dest_y);
        
        int get_hit_points();
        void hit(const int amount); // Reduce hp by amount without overflow
        void die(int* spawn); // Will probably respawn the player, awatining decisions

        int get_team();

        int get_id();

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

        void onhit();

        int get_next_x();

        int get_next_y();

        short get_number();

        int get_speed();
        std::string encode_player();

        void status_effect_invisible();
        void status_effect_frozen();

    private:
        short team;
        int speed;
        int old_x;
        int old_y;
        int dest_x;
        int dest_y;
        int hit_points=100;
        int lastgoodposx;
        int lastgoodposy;
        int count;
        const char base_health = 100;
        bool damaged;
        bool havechanged;
        int game_state;
        int respawn_timer;
        int status_effect_timeout_frozen;
        int status_effect_timeout_invisible;
        bool prevent_movement;
        short number; //this is the id of the player (useful for the server)
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
