#pragma once
#include "Map.hpp"

class Gamestatus {
    public:
    Gamestatus(short gs, Map* m);
    short game_state;
    Map* map;
    int* playerNumber;
    protected:
    private:
};