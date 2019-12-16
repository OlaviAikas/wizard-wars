#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include "../headers/Spells.hpp"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../headers/Interface.hpp"
#include <allegro5/allegro_primitives.h>

Map::Map(const char* name, Interface *interface) {
    this->map = al_load_bitmap(name);
    this->interface = interface;
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
            if (*i == *j) {
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


std::string Map::encode_players(){
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
std::string Map::encode_controlpoint(){
    std::string to_transmit="";
    Controlpoint::Controlpoint i;
    std::stringstream ss;
    ss << i->get_number();        
    std::string number = ss.str();
    ss << i->get_owner();
    std::string owner = ss.str();
    ss << i->get_timegot();
    std::string timegot = ss.str();
    ss << i->get_timetoget();
    std::string timetoget = ss.str();      
    to_transmit="1"+owner+"."+timegot+"."+timetoget+"."+number+":";
    }
    return to_transmit;git 


}

std::string Map::encode_spells(){
    std::string to_transmit="";
    for (std::list<Spells>::iterator i = spells.begin(); i != spells.end(); i++){
        std::stringstream ss;
        //ss << i->get_number(); 
        //std::string number = ss.str();
        ss << i->get_x(); 
        std::string x = ss.str();
        ss << i->get_y(); 
        std::string y = ss.str();
        ss << i->get_dir_x(); 
        std::string dir_x = ss.str();
        ss << i->get_desty(); 
        std::string desty = ss.str();
        to_transmit="0"+"."+x+"."+y+"."+dir_x+"."+dir_y+":";

}
}
        
