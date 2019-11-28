#define DEBUG_MODE
#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

Map::Map(const char* name) {
    this->map = al_load_bitmap(name);
}

Map::~Map() {
    al_destroy_bitmap(map);
}

void Map::draw_map(int camera_x, int camera_y) {
    al_draw_bitmap_region(map, camera_x, camera_y, 1920, 1080, 0, 0, 0);
}

void Map::check_collisions() {
#ifdef DEBUG_MODE
    std::cout << "check_collisions called" << std::endl;
#endif
    for (std::list<Player>::iterator i = players.begin(); i != players.end(); i++) {
#ifdef DEBUG_MODE
        std::cout << "for00 ";
        std::cout << &(*i) << std::endl;
#endif
        // std::list<Player>::iterator b = i++;
        // if (b != players.end() ) {
            for (std::list<Player>::iterator j = i++; j != players.end(); j++) {
#ifdef DEBUG_MODE
                std::cout << "for01 ";
                std::cout << &(*j) << std::endl;
#endif
                if (*i == *j) {
#ifdef DEBUG_MODE
                    std::cout << "for02 ";
                    std::cout << &(*i) << "==" << &(*j) << std::endl;
#endif
                    i->on_collision(*j);
                    j->on_collision(*i);
                }
            }
        // }
        for (std::list<Spell>::iterator j = spells.begin(); j != spells.end(); j++) {
#ifdef DEBUG_MODE
            std::cout << "for03 ";
            std::cout << &(*j) << std::endl;
#endif
            if (*i == *j) {
#ifdef DEBUG_MODE
                std::cout << "for04 ";
                std::cout << &(*i) << "==" << &(*j) << std::endl;
#endif
                i->on_collision(*j);
#ifdef DEBUG_MODE
                std::cout << "for05 ";
                std::cout << &(*i) << ".on_collision>" << &(*j) << std::endl;
#endif
                j->on_collision(*i);
#ifdef DEBUG_MODE
                std::cout << "for06 ";
                std::cout << &(*j) << ".on_collision>" << &(*i) << std::endl;
#endif
            }
        }
        for (std::list<MapObject>::iterator j = statics.begin(); j != statics.end(); j++) {
#ifdef DEBUG_MODE
            std::cout << "for05";
#endif
            if (*i == *j) {
#ifdef DEBUG_MODE
                std::cout << "for06";
#endif
                i->on_collision(*j);
                j->on_collision(*i);
            }
        }
    }
    for (std::list<Spell>::iterator i = spells.begin(); i != spells.end(); i++) {
#ifdef DEBUG_MODE
        std::cout << "for07: i at " << &(*i) << std::endl;
        std::cout << "for07: i at " << &(*i) << " with i++ at " << &(*i++) << " with spells.end at " << &(*spells.end()) << std::endl;
#endif
        // std::list<Spell>::iterator b = i++;
        if (i++ != spells.end()) {
            for (std::list<Spell>::iterator j = i++; j != spells.end(); j++) {
#ifdef DEBUG_MODE
                std::cout << "for08";
#endif
                if (*i == *j) {
#ifdef DEBUG_MODE
                    std::cout << "for09";
#endif

                    i->on_collision(*j);
                    j->on_collision(*i);
                }
            }
        }
        for (std::list<MapObject>::iterator j = statics.begin(); j != statics.end(); j++) {
            if (*i == *j) {
                i->on_collision(*j);
                j->on_collision(*i);
            }
        }
    }
}

std::list<Player>::iterator Map::fetch_pit(short n) {
    std::list<Player>::iterator it = this->players.begin();
    while (it->get_number() != n) {
        it++;
    }
    return it;
}