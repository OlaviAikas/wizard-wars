#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

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
    for (std::list<Player>::iterator i = players.begin(); i != players.end(); i++) {
        for (std::list<Player>::iterator j = i++; j != players.end(); j++) {
            if (*i == *j) {
                i->on_collision(*j);
                j->on_collision(*i);
            }
        }
        for (std::list<MapObject>::iterator j = spells.begin(); j != spells.end(); j++) {
            if (*i == *j) {
                i->on_collision(*j);
                j->on_collision(*i);
            }
        }
        for (std::list<MapObject>::iterator j = statics.begin(); j != statics.end(); j++) {
            if (*i == *j) {
                i->on_collision(*j);
                j->on_collision(*i);
            }
        }
    }
    for (std::list<MapObject>::iterator i = spells.begin(); i != spells.end(); i++) {
        for (std::list<MapObject>::iterator j = i++; j != spells.end(); j++) {
            if (*i == *j) {
                i->on_collision(*j);
                j->on_collision(*i);
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

std::string Map::encode_player(){
    std::string to_transmit="";
    for (std::list<Player>::iterator i = players.begin(); i != players.end(); i++){
        std::stringstream ss;
        ss << i->get_number(); //Write the number
        std::string number = ss.str();
        ss << i->get_x(); //Write the x
        std::string x = ss.str();
        ss << i->get_y(); //Write the y
        std::string y = ss.str();
        ss << i->get_destx(); //Write the destx
        std::string destx = ss.str();
        ss << i->get_desty(); //Write the desty
        std::string desty = ss.str();
        to_transmit="0"+number+"."+x+"."+y+"."+destx+"."+desty+":";
    }
    return to_transmit;
}