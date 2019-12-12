#pragma once
#include <allegro5/allegro.h>
#include <list>
#include "Player.hpp"
#include "MapObject.hpp"
#include "Spells.hpp"

class Map {
    public:
        Map(const char* name);
        ~Map();

        void draw_map(int camera_x, int camera_y);

        void check_collisions();
        void garbage_collect();

        std::list<Player*> players;
        std::list<Spell*> spells;
        std::list<MapObject*> statics;

        template <typename T> void draw_list(std::list<T> &list, int camera_x, int camera_y) {
            for (typename std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                (*i)->draw(camera_x, camera_y);
            }
        }

        template <typename T> void move_list(std::list<T> &list) {
            for (typename std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                (*i)->move();
                if ((*i)->get_x() > 3840 || (*i)->get_x() < 0 || (*i)->get_y() > 2160 || (*i)->get_y() < 0) {
                    delete *i;
                    i = list.erase(i);
                    // i--;
                } 
            }
        }

        template <typename T> void garbage_collect_list(std::list<T> &list) {
            for (typename std::list<T>::iterator i = list.begin(); i != list.end(); i++) {
                if ((*i)->get_garbage_collect()) {
                    delete *i;
                    i = list.erase(i);
                    // i--;
                }
            }
        }

        std::list<Player*>::iterator fetch_pit(short n);
       // still not sure: std::list<Spell>::iterator fetch_spit(short n);
    private:
        ALLEGRO_BITMAP* map;
};
