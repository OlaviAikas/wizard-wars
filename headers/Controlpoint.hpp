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

        void on_collision(Player other);

        int get_timegot();
        int get_timetoget();
        void change_tgot(int tgot);
        void change_ttoget(int ttoget);
        void change_owner(bool updated);
        bool get_havechanged();
        void reset_havechanged();

    private:
        bool owner;
        int timegot=0;
        int timetoget=450;
        int number;
        bool havechanged;
};