#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <list>
#include "Interface.hpp"
#include "Player.hpp"
#include "MapObject.hpp"
#include "Spells.hpp"
#include "Controlpoint.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>


class Map {
    public:
        Map(const char* name, Interface *interface);
        ~Map();

        void draw_map(int camera_x, int camera_y);

        void check_collisions();

        std::string encode_player(Player &i);
        std::string encode_controlpoint(Controlpoint &i);
        std::string encode_spell(Spell &s);
    
        void update_player(std::string mes_get);
        void update_controlpoint(std::string mes_get);
        void update_spell(std::string mes_get);
        void update_with_message(std::string mes_get);

        void transmit_changes();

        std::list<Player*> players;
        std::list<Spell*> spells;
        std::list<Controlpoint*> controlpoints;
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
                    i--;
                } 
            }
        }

        std::list<Player*>::iterator fetch_pit(short n);
       // still not sure: std::list<Spell>::iterator fetch_spit(short n);
    private:
        ALLEGRO_BITMAP* map;
        Interface* interface;
};
