#pragma once
#include <list>
#include "Player.hpp"

class Map {
    public:
        std::list<Player> players;

        template <typename T> void draw_list(std::list<T>); //Iterates over a list and calls draw() of each element
        template <typename T> void move_list(std::list<T>); //Iterates over a list and calls mmove() of each element
};