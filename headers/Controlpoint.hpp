#pragma once
#include "MapObject.hpp"
#include "Player.hpp"
#include <list>

class Controlpoint : public MapObject {
    public:
        Controlpoint(int x, int y, int number, int side, int owner);
        ~Controlpoint();

        void set_owner(short newowner);

        bool get_owner();

        short get_number();

        using MapObject::on_collision;
        virtual void on_collision(Player &other);

        void draw(int camera_x, int camera_y);

        int get_timegot();
        int get_timetoget();
        void change_tgot(int tgot);
        void change_ttoget(int ttoget);
        void change_owner(bool updated);
        bool get_havechanged();
        void reset_havechanged();

    private:
        char owner;
        int timegot=0;
        int timetoget=180;
        int number;
		bool contested=false;
        bool havechanged;
        int is_someone=false;
		ALLEGRO_BITMAP* control_blue = al_load_bitmap("resources/Controlpoint!3.bmp");
		ALLEGRO_BITMAP* control_red = al_load_bitmap("resources/Controlpoint!2.bmp");
		ALLEGRO_BITMAP* control_neutral = al_load_bitmap("resources/Controlpoint!1.bmp");
};