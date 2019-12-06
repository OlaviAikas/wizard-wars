#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include "../headers/Spells.hpp"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

Map::Map(const char* name) {
    this->map = al_load_bitmap(name);
}

Map::~Map() {
    al_destroy_bitmap(map);
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        delete *i;
    }
    for (std::list<Spell*>::iterator i = spells.begin(); i != spells.end(); i++) {
        delete *i;
    }
    for (std::list<MapObject*>::iterator i = statics.begin(); i != statics.end(); i++) {
        delete *i;
    }
}

void Map::draw_map(int camera_x, int camera_y) {
    al_draw_bitmap_region(map, camera_x, camera_y, 1920, 1080, 0, 0, 0);
}

void Map::check_collisions() {
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        for (std::list<Player*>::iterator j = std::next(i,1); j != players.end(); j++) {
            if (**i == **j) {
                (*i)->on_collision(**j);
                (*j)->on_collision(**i);
            }
        }
        for (std::list<Spell*>::iterator j = spells.begin(); j != spells.end(); j++) {
            if (**i == **j) {
                (*i)->on_collision(**j);
                (*j)->on_collision(**i);
            }
        }
        for (std::list<MapObject*>::iterator j = statics.begin(); j != statics.end(); j++) {
            if (**i == **j) {
                (*i)->on_collision(**j);
                (*j)->on_collision(**i);
            }
        }
    }
    for (std::list<Spell*>::iterator i = spells.begin(); i != spells.end(); i++) {
        for (std::list<Spell*>::iterator j = std::next(i,1); j != spells.end(); j++) {
            if (*i == *j) {
                (*i)->on_collision(**j);
                (*j)->on_collision(**i);
            }
        }
        for (std::list<MapObject*>::iterator j = statics.begin(); j != statics.end(); j++) {
            if (*i == *j) {
                (*i)->on_collision(**j);
                (*j)->on_collision(**i);
            }
        }
    }
}

std::list<Player*>::iterator Map::fetch_pit(short n) {
    std::list<Player*>::iterator it = this->players.begin();
    while ((*it)->get_number() != n) {
        it++;
    }
    return it;
}