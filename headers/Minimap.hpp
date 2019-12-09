#pragma once
#include "HUDobject.hpp"
#include <allegro5/allegro5.h>
#include <list>
#include "../headers/Player.hpp"

class Minimap : public HUDobject {
    public:
        Minimap(const char* name, int win_x, int win_y);
        void update();
        void draw(std::list<Player*> players);

    private:
        ALLEGRO_BITMAP* map;
};