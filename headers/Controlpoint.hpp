#pragma once
#include "MapObject.hpp"
#include "Player.hpp"
#include <list>

class Controlpoint : public MapObject {
    public:
        Controlpoint(int x, int y, int number, int side, bool owner);

        void set_owner(short newowner);

        bool get_owner();

        short get_number();

        using MapObject::on_collision;
        virtual void on_collision(Player &other);

        void draw(int camera_x, int camera_y);

    private:
        bool owner;
        int timegot=0;
        int timetoget=450;
        int number;
        int is_someone=false;
};