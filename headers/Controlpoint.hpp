#pragma once
#include "MapObject.hpp"
#include "Map.hpp"
#include <list>

class Controlpoint : public MapObject {
    public:
        Controlpoint(int x, int y, int number, int side, bool owner);

        void set_owner(short newowner);

        bool get_owner();

        short get_number();

        void on_collision(Player other);

    private:
        bool owner;
        int timegot=0;
        int timetoget=450;
        int number;
};