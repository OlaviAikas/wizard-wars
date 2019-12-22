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


std::string Map::encode_player(Player &i){
    std::string to_transmit="";
    
    std::stringstream ss;
    ss << i.get_number(); //Write the number
    std::string number = ss.str();
    ss << i.get_x(); //Write the x
    std::string x = ss.str();
    ss << i.get_y(); //Write the y
    std::string y = ss.str();
    ss << i.get_dest_x(); //Write the destx
    std::string destx = ss.str();
    ss << i.get_dest_y(); //Write the desty
    std::string desty = ss.str();
    to_transmit="0."+number+"."+x+"."+y+"."+destx+"."+desty+".:";
    i.reset_havechanged();
    return to_transmit;
}
std::string Map::encode_controlpoint(Controlpoint &i){
    std::string to_transmit="";
    std::stringstream ss;
    ss << i.get_number();        
    std::string number = ss.str();
    ss << i.get_owner();
    std::string owner = ss.str();
    ss << i.get_timegot();
    std::string timegot = ss.str();
    ss << i.get_timetoget();
    std::string timetoget = ss.str();      
    to_transmit="1."+number+'.'+owner+"."+timegot+"."+timetoget+".:";
    i.reset_havechanged();
    return to_transmit;
}

std::string Map::encode_spell(Spell &i){
    std::string to_transmit="";
    
    std::stringstream ss;
    //ss << i->get_number(); 
    //std::string number = ss.str();
    ss << i.get_x(); 
    std::string x = ss.str();
    ss << i.get_y(); 
    std::string y = ss.str();
    ss << i.get_dir_x(); 
    std::string dir_x = ss.str();
    ss << i.get_dir_y(); 
    std::string dir_y = ss.str();
    to_transmit="2."+x+"."+y+"."+dir_x+"."+dir_y+".:";
    i.reset_havechanged();
    return to_transmit;
}

void Map::update_with_message(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    if(std::stoi(mes[0])==0){
        Map::update_player(mes_get);
    }
    if(std::stoi(mes[0])==1){
        Map::update_controlpoint(mes_get);
    }
    if(std::stoi(mes[0])==2){
        Map::update_spell(mes_get);
    }
}

void Map::update_player(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        if ((*i)->get_number()==std::stoi(mes[1]) && (*i)->get_number() != *(interface->game_status->playerNumber)){
            (*i)->change_x(std::stoi(mes[2]));
            (*i)->change_y(std::stoi(mes[3]));
            (*i)->change_destx(std::stoi(mes[4]));
            (*i)->change_desty(std::stoi(mes[5]));
            (*i)->reset_havechanged();
            return;
        }
    }
    // player does not exist yet -> add new player
    
    players.push_back(new Player(std::stoi(mes[2]), std::stoi(mes[3]), std::stoi(mes[1])));
}

void Map::update_controlpoint(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    for (std::list<Controlpoint*>::iterator i = controlpoints.begin(); i != controlpoints.end(); i++) {
        if ((*i)->get_number()==std::stoi(mes[1])){
            (*i)->change_owner(std::stoi(mes[2]));
            (*i)->change_tgot(std::stoi(mes[3]));
            (*i)->change_ttoget(std::stoi(mes[4]));
            (*i)->reset_havechanged();
            return;
        }
    }
    // controlpoint does not exist yet -> add?
    std::cout << "error: controlpoint does not exist" << std::endl;
}

void Map::update_spell(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    // todo -> implement spell id + add spell if neccessary (identify spell type with id?) + update position of all spells
    
//not sure what changes in spell class mean; spells don't have number to identify and iterate
} 

void Map::transmit_changes(){
    std::stringstream ss;
    for (std::list<Controlpoint*>::iterator i = controlpoints.begin(); i != controlpoints.end(); i++) {
        if(i->get_havechanged()){
            ss << encode_controlpoint(*i);
        }
    }
    for (std::list<Spell*>::iterator i = spells.begin(); i != spells.end(); i++) {
        if(i->get_havechanged()){
            ss << encode_spell(*i);
        }
    }        
    for (std::list<Player*>::iterator j = std::next(i,1); j != players.end(); j++) {
        if(i->get_havechanged()){
            ss << encode_player(*i);
        }
    }
    interface->send_message(ss.str());
}