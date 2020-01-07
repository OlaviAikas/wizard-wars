#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include "../headers/Spells.hpp"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../headers/Interface.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>

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

int* Map::get_lives(){
    return this->lives;
}

void Map::set_spawnpoints(int x1, int y1, int x2, int y2){
    spawnpoint1[0] = x1;
    spawnpoint1[1] = y1;
    spawnpoint2[0] = x2;
    spawnpoint2[1] = y2;
}

void Map::modif_lives(int lives1, int lives2){
    lives[0]=lives1;
    lives[1]=lives2;
}

void Map::check_dead(){
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        if (((*i)->get_hit_points()<=0)&&((*i)->get_noclip()==false)){
            int* spawn;
            if ((*i)->get_team()){
                this->lives[0]-=1;
                spawn = this->spawnpoint1;
            }
            else{
                this->lives[1]-=1;
                spawn = this->spawnpoint2;
            }
            (*i)->die(spawn);
        }
    }
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
        for (std::list<Controlpoint*>::iterator j = cp.begin(); j != cp.end(); j++) {
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

void Map::garbage_collect() {
    garbage_collect_list(players);
    garbage_collect_list(spells);
    garbage_collect_list(statics);
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

void Map::decode_message(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    if(std::stoi(mes[0])==0){
        Map::decode_players(mes_get);
    }
    if(std::stoi(mes[0])==1){
        Map::decode_controlpoints(mes_get);
    }
    if(std::stoi(mes[0])==2){
        Map::decode_spells(mes_get);
    }
}

void Map::decode_players(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        if ((*i)->get_number()==std::stoi(mes[1])){

            (*i)->change_x(std::stoi(mes[2]));
            (*i)->change_y(std::stoi(mes[3]));
            (*i)->change_destx(std::stoi(mes[4]));
            (*i)->change_desty(std::stoi(mes[5]));
            (*i)->reset_havechanged();
        }
    }
}

void Map::decode_controlpoints(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
    for (std::list<Controlpoint*>::iterator i = controlpoints.begin(); i != controlpoints.end(); i++) {
        if ((*i)->get_number()==std::stoi(mes[1])){
            (*i)->change_owner(std::stoi(mes[2]));
            (*i)->change_tgot(std::stoi(mes[3]));
            (*i)->change_ttoget(std::stoi(mes[4]));
            (*i)->reset_havechanged();
        }
    }
}

void Map::decode_spells(std::string mes_get){
    std::vector<std::string> mes;
    boost::split(mes, mes_get, boost::is_any_of("."));
//not sure what changes in spell class mean; spells don't have number to identify and iterate
} 