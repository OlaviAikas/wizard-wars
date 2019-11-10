#pragma once
#include <list>
#include "Player.hpp"
#include "MapObject.hpp"

class Map {
    public:
        std::list<Player> players;
        std::list<MapObject> spells;
        std::list<MapObject> statics;

        template <typename T> void draw_list(std::list<T> list) {
            for (std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                i.draw();
            }
        }

        template <typename T> void move_list(std::list<T> list) {
            for (std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                i.move();
            }
        }
};