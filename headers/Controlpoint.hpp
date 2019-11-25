#pragma once
#include "MapObject.hpp"
#include "Map.hpp"
#include <list>

class Controlpoint : public MapObject {
    public:
        Controlpoint(int x, int y, int number, int range);

        void capture(Map map);

        void set_owner(short newowner);

        bool in_capture_range(MapObject other);

        short get_owner();

        short get_number();

    private:
        short owner;
        int timetoget=15;
        int range=200;
        int x;
        int y;
        int number;
};