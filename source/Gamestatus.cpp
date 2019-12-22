#include "../headers/Gamestatus.hpp"

Gamestatus::Gamestatus(short gs, Map* m, int *pn){
    game_state = gs;
    map = m;
    playerNumber = pn;
};