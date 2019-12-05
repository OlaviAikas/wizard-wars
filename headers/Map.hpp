#pragma once
#include <allegro5/allegro.h>
#include <list>
#include <string>
#include "Player.hpp"
#include "Controlpoint.hpp"
#include "MapObject.hpp"
#include <sstream>

class Map {
    public:
        Map(const char* name);
        ~Map();

        void draw_map(int camera_x, int camera_y);

        void check_collisions();

        std::list<Player> players;
        std::list<MapObject> spells;
        std::list<MapObject> statics;

        template <typename T> void draw_list(std::list<T> &list, int camera_x, int camera_y) {
            for (typename std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                i->draw(camera_x, camera_y);
            }
        }

        template <typename T> void move_list(std::list<T> &list) {
            for (typename std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                i->move();
            }
        }

        std::list<Player>::iterator fetch_pit(short n);

        std::string encode_player();

        std::string encode_controlpoint();

    private:
        ALLEGRO_BITMAP* map;
};
