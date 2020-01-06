#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <list>
#include "Player.hpp"
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Interface.hpp"
#include "Controlpoint.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>

#include "Controlpoint.hpp"

class Map {
    public:
        Map(const char* name, Interface *interface);
        ~Map();

        void draw_map(int camera_x, int camera_y);

        void check_collisions();
        void garbage_collect();
        int* get_lives();
        void modif_lives(int lives1, int lives2);
        void check_dead();
        void set_spawnpoints(int x1, int y1, int x2, int y2);

        std::string encode_player(Player &i);
        std::string encode_controlpoint(Controlpoint &i);
        std::string encode_spell(Spell &s);
    
        void decode_players(std::string mes_get);
        void decode_controlpoints(std::string mes_get);
        void decode_spells(std::string mes_get);
        void decode_message(std::string mes_get);

        std::list<Player*> players;
        std::list<Spell*> spells;
        std::list<Controlpoint*> controlpoints;
        std::list<MapObject*> statics;
        std::list<Controlpoint*> cp;

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
        Interface* interface;
        int lives[2];
        int spawnpoint1[2];
        int spawnpoint2[2];
};
