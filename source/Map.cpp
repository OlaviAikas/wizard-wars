#include "../headers/Map.hpp"
#include "../headers/Player.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Rock.hpp"
#include "../headers/FirePellet.hpp"
#include "../headers/Ice.hpp"
#include "../headers/HealP.hpp"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../headers/Interface.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../headers/DZone.hpp"
#include "../headers/FogZone.hpp"
#include "../headers/HealFireZone.hpp"
#include "../headers/HealZone.hpp"
#include "../headers/FreezeZone.hpp"
#include "../headers/WaterB.hpp"
#include "../headers/HealB.hpp"
#include "../headers/DealingB.hpp"
#include "../headers/MainShield.hpp"

Map::Map(const char* name) {
    this->map = al_load_bitmap(name);
    this->spawns[0] = 1;
    this->spawns[1] = 0;
    this->spawns[2] = 0;
    this->spawns[3] = 2;
    iam=true;
    iamnot=false;
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


void Map::set_spawnpoints(int x1, int y1, int x2, int y2,int x3, int y3){
    spawnpoint1[0] = x1;
    spawnpoint1[1] = y1;
    spawnpoint2[0] = x2;
    spawnpoint2[1] = y2;
    spawnpoint3[0] = x3;
    spawnpoint3[1] = y3;
}

void Map::modif_lives(int team , bool change){
    if (team == 1){
        spawnred = change;
    }
    if (team == 2){
        spawnblue = change;
    }
}

int Map::get_winner(){
    return this->winner;
}

void Map::check_dead(){
    int k = 0;
    for (std::list<Controlpoint*>::iterator i = cp.begin(); i != cp.end(); i++){
        this->spawns[k] = (*i)->get_owner();//this iterates over the control points to update what belongs to who
        k +=1;
    }
    if (spawns[0] == spawns[1] && spawns[0] == spawns[2]){//Here we check if one teams controls all the points
        if (spawns[0] == 1){
            spawnblue = false; //red team controls all the points
        }
        else if (spawns[0] == 2){
            spawnred = false; //blue team controls all the points
        }
    }
    else{
        spawnblue = true;
        spawnred = true;
    }
    srand(time(NULL));
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        if (((*i)->get_hit_points()<=0)&&((*i)->get_noclip()==false)){
            int spawn1 = 0;
            int spawn2 = 0;
            int k = rand()%3;
            int R = rand()%150;
            double theta = rand()%360;
            double ang = cos(theta);
            std::cout << k << std::endl;
            if ((*i)->get_team()==1){
                //spawn = spawnpoint1;//Randomize the spawns
                if (k == 0 && spawns[0] == 1){
                    spawn1 = spawnpoint1[0] + R*ang;
                    spawn2 = spawnpoint1[1] + R*ang;
                }
                else if (k == 1 && spawns[1] == 1){
                        spawn1 = spawnpoint2[0] + R*ang;
                        spawn2 = spawnpoint2[1] + R*ang;
                }
                else if (k == 2 && spawns[2] == 1){
                    spawn1 = spawnpoint3[0] + R*ang;
                    spawn2 = spawnpoint3[1] + R*ang;
                }
                else{
                    spawn1 = spawnpoint1[0] + R*ang;
                    spawn2 = spawnpoint1[1] + R*ang;
                }
                if (not spawnred){
                    (*i)->change_spawnable(false); //Tells the player class that it cant spawn anymore
                }
                else{
                    (*i)->change_spawnable(true);
                }
            }
            else{
                
                if (k == 0 && spawns[0] == 2){
                    spawn1 = spawnpoint1[0] + R*ang;
                    spawn2 = spawnpoint1[1] + R*ang;
                }
                else if (k == 1 && spawns[1] == 2){
                    spawn1 = spawnpoint2[0] + R*ang;
                    spawn2 = spawnpoint2[1] + R*ang;
                }
                else if (k == 2 && spawns[2] == 2){
                    spawn1 = spawnpoint3[0] + R*ang;
                    spawn2 = spawnpoint3[1] + R*ang;
                }
                else{
                    spawn1 = spawnpoint3[0] + R*ang;
                    spawn2 = spawnpoint3[1] + R*ang;
                }
                if (not spawnblue){
                    (*i)->change_spawnable(false); //Tells the player class that it cant spawn anymore
                }
                else{
                    (*i)->change_spawnable(true);
                }
                
            }
            std::cout<<spawn1<<std::endl;
            std::cout<<spawn2<<std::endl;
            (*i)->change_curspawn(spawn1,spawn2);
            (*i)->die();
        }
    }
}

bool Map::game_ended(){
    if (not spawnred){ //If the players of the red team cant spawn
        short k = 0;
        for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++){
            if ((*i)->get_team()==1)
            {
                if ((*i)->check_dead()){
                k +=1;
                }
            }
        }
        if (k == 1){
            this-> winner = 2;
            return true; //This means that all the players are dead 
        }
    }
    if (not spawnblue){
        short g = 0;
        for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++){
            if ((*i)->get_team()==2)
            {
                if ((*i)->check_dead()){
                g +=1;
                }
            }
        }
        if (g == 1){//this value will depend on the amount of players
            this-> winner = 1;
            return true; //This means that all the players are dead and the red team wins
        }
    }
    return false;
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
        for (std::list<Controlpoint*>::iterator j = cp.begin(); j != cp.end(); j++) {
            if (**i == **j) {
                (*i)->on_collision(**j);
                (*j)->on_collision(**i);
            }
        }
    }
    for (std::list<Spell*>::iterator i = spells.begin(); i != spells.end(); i++) {
        for (std::list<Spell*>::iterator j = std::next(i,1); j != spells.end(); j++) {
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
}

void Map::garbage_collect() {
    garbage_collect_list(players);
    garbage_collect_list(spells);
    garbage_collect_list(statics);
    garbage_collect_list(cp);
}

std::list<Player*>::iterator Map::fetch_pit(short n) {
    std::list<Player*>::iterator it = this->players.begin();
    while ((*it)->get_id() != n) {
        it++;
    }
    return it;
}

int Map::decode_players(std::string mes_get, short client_number){
    int a=0;
    std::vector<std::string> mes1;
    boost::split(mes1, mes_get, boost::is_any_of(":"));
    for(unsigned int j=1; j<mes1.size(); j++){
        for(int a=0; a==10; a++){
            mes1[j].erase(0, 1);
        }
        std::vector<std::string> mes2;
        boost::split(mes2, mes1[j], boost::is_any_of("."));
        if(mes1.size()==2){
            a=stoi(mes2[2]);
        }
        for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
            if ((*i)->get_number()!=client_number&&(*i)->get_number()==std::stoi(mes2[2])){
                (*i)->change_x(std::stoi(mes2[3]));
                (*i)->change_y(std::stoi(mes2[4]));
                (*i)->change_destx(std::stoi(mes2[5]));
                (*i)->change_desty(std::stoi(mes2[6]));
                (*i)->set_hitpoints(std::stoi(mes2[7]));
                (*i)->set_count(std::stoi(mes2[8]));
                (*i)->set_timer(std::stoi(mes2[9]));
                (*i)->set_frozen(std::stoi(mes2[10]));
                (*i)->set_prevent(mes2[11]=="1");
                (*i)->reset_havechanged();
            }
        }
    }
    return a;
}

void Map::decode_spells(std::string mes_get){
    std::vector<std::string> mes1;
    boost::split(mes1, mes_get, boost::is_any_of(":"));
    if(mes1.size()==1){
        std::cout<<"Resized"<<std::endl;
        mes1.resize(2);
        mes1[1]=mes1[0];
    }
    for(unsigned int j=1; j<mes1.size(); j++){
        bool found=false;
        std::vector<std::string> mes2;
        boost::split(mes2, mes1[j], boost::is_any_of(";"));
        for (std::list<Spell*>::iterator i = spells.begin(); i != spells.end(); i++) {
            if ((*i)->get_id()==std::stoi(mes2[1])){
                found=true;
                std::cout<<"Found"<<std::endl;
                if(std::stoi(mes2[2])==0){
                    (*i)->set_x(std::stoi(mes2[8]));
                    (*i)->set_y(std::stoi(mes2[9]));
                    std::cout<<"Found projectile"<<std::endl;
                }
                if(std::stoi(mes2[2])==1){
                    (*i)->set_x(std::stoi(mes2[8]));
                    (*i)->set_y(std::stoi(mes2[9]));
                    std::cout<<"Found zone"<<std::endl;
                }
                // if(std::stoi(mes2[2])==2){
                //     (*i)->counter=0;
                //     (*i)->set_x(std::stoi(mes2[8]));
                //     (*i)->set_y(std::stoi(mes2[9]));
                //     std::cout<<"Found beam"<<std::endl;
                // }
            }
        }
        if(!found){
            std::cout<<"Not found"<<std::endl;
            if(std::stoi(mes2[2])==0){
                std::cout<<"Creating projectile"<<std::endl;
                bool a[5]={false, stoi(mes2[3])==1, stoi(mes2[4])==1, stoi(mes2[5])==1, stoi(mes2[6])==1};
                if(std::stoi(mes2[7])==0){
                    spells.push_back(new Rock(stoi(mes2[8]), stoi(mes2[9]), stof(mes2[10]),stof(mes2[11]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==1){
                    spells.push_back(new FireP(stoi(mes2[8]), stoi(mes2[9]), stof(mes2[10]),stof(mes2[11]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==2){
                    spells.push_back(new Ice(stoi(mes2[8]), stoi(mes2[9]), stof(mes2[10]),stof(mes2[11]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==3){
                    spells.push_back(new HealP(stoi(mes2[8]), stoi(mes2[9]), stof(mes2[10]),stof(mes2[11]), stoi(mes2[1]), a));
                }
            }
            if(std::stoi(mes2[2])==1){
                std::cout<<"Creating Zone"<<std::endl;
                bool a[5]={false, stoi(mes2[3])==1, stoi(mes2[4])==1, stoi(mes2[5])==1, stoi(mes2[6])==1};
                if(std::stoi(mes2[7])==0){
                    spells.push_back(new DamageZ(stoi(mes2[8]),stoi(mes2[9]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==1){
                    spells.push_back(new FogZ(stoi(mes2[8]),stoi(mes2[9]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==2){
                    spells.push_back(new FreezeZ(stoi(mes2[8]),stoi(mes2[9]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==3){
                    spells.push_back(new HealZ(stoi(mes2[8]),stoi(mes2[9]), stoi(mes2[1]), a));
                }
                if(std::stoi(mes2[7])==4){
                    spells.push_back(new HealFireZ(stoi(mes2[8]),stoi(mes2[9]), stoi(mes2[1]), a));
                }
            }
            if(std::stoi(mes2[2])==3){
                std::cout<<"Creating Shield"<<std::endl;
                bool a[5]={false, stoi(mes2[3])==1, stoi(mes2[4])==1, stoi(mes2[5])==1, stoi(mes2[6])==1};
                if(std::stoi(mes2[7])==0){
                    spells.push_back(new MainShield(stoi(mes2[8]),stoi(mes2[9]), stof(mes2[10]), stof(mes2[11]), stoi(mes2[12])==1, stoi(mes2[1]), a));
                }
            }
    //         if(std::stoi(mes2[2])==2){
    //             std::cout<<"Creating Beam"<<std::endl;
    //             bool a[5]={false, stoi(mes2[3])==1, stoi(mes2[4])==1, stoi(mes2[5])==1, stoi(mes2[6])==1};
    //             if(std::stoi(mes2[7])==0){ 
    //                 std::list<Player*>::iterator pit=fetch_pit(stoi(mes2[12])); 
    //                 float dx=stof(mes2[10]);
    //                 float* dxp=&dx; 
    //                 float dy=stof(mes2[11]);
    //                 float* dyp=&dy;
    //                 spells.push_back(new DealingB(pit,dxp,dyp,&iam,this,stoi(mes2[1]), a));
    //             }
    //             if(std::stoi(mes2[7])==1){
    //                 std::list<Player*>::iterator pit=fetch_pit(stoi(mes2[12])); 
    //                 float dx=stof(mes2[10]);
    //                 float* dxp=&dx; 
    //                 float dy=stof(mes2[11]);
    //                 float* dyp=&dy; 
    //                 spells.push_back(new HealB(pit,dxp,dyp,&iam,this,stoi(mes2[1]), a));
    //             }
    //             if(std::stoi(mes2[7])==2){
    //                 std::list<Player*>::iterator pit=fetch_pit(stoi(mes2[12])); 
    //                 float dx=stof(mes2[10]);
    //                 float* dxp=&dx; 
    //                 float dy=stof(mes2[11]);
    //                 float* dyp=&dy;
    //                 spells.push_back(new WaterB(pit,dxp,dyp,&iam,this,stoi(mes2[1]), a));
    //             }
    //         }
    //     }
    }
}

// std::string Map::encode_player(Player &i){
//     std::string to_transmit="";
    
//     std::stringstream ss;
//     ss << i.get_number(); //Write the number
//     std::string number = ss.str();
//     ss << i.get_x(); //Write the x
//     std::string x = ss.str();
//     ss << i.get_y(); //Write the y
//     std::string y = ss.str();
//     ss << i.get_dest_x(); //Write the destx
//     std::string destx = ss.str();
//     ss << i.get_dest_y(); //Write the desty
//     std::string desty = ss.str();
//     to_transmit="0."+number+"."+x+"."+y+"."+destx+"."+desty+".:";
//     i.reset_havechanged();
//     return to_transmit;
// }
// std::string Map::encode_controlpoint(Controlpoint &i){
//     std::string to_transmit="";
//     std::stringstream ss;
//     ss << i.get_number();        
//     std::string number = ss.str();
//     ss << i.get_owner();
//     std::string owner = ss.str();
//     ss << i.get_timegot();
//     std::string timegot = ss.str();
//     ss << i.get_timetoget();
//     std::string timetoget = ss.str();      
//     to_transmit="1."+number+'.'+owner+"."+timegot+"."+timetoget+".:";
//     i.reset_havechanged();
//     return to_transmit;
// }

// std::string Map::encode_spell(Spell &i){
//     std::string to_transmit="";
    
//     std::stringstream ss;
//     //ss << i->get_number(); 
//     //std::string number = ss.str();
//     ss << i.get_x(); 
//     std::string x = ss.str();
//     ss << i.get_y(); 
//     std::string y = ss.str();
//     ss << i.get_dir_x(); 
//     std::string dir_x = ss.str();
//     ss << i.get_dir_y(); 
//     std::string dir_y = ss.str();
//     to_transmit="2."+x+"."+y+"."+dir_x+"."+dir_y+".:";
//     i.reset_havechanged();
//     return to_transmit;
// }

// void Map::decode_message(std::string mes_get){
//     std::vector<std::string> mes;
//     boost::split(mes, mes_get, boost::is_any_of("."));
//     if(std::stoi(mes[0])==0){
//         Map::decode_players(mes_get);
//     }
//     if(std::stoi(mes[0])==1){
//         Map::decode_controlpoints(mes_get);
//     }
//     if(std::stoi(mes[0])==2){
//         Map::decode_spells(mes_get);
//     }
// }

// void Map::decode_players(std::string mes_get){
//     std::vector<std::string> mes;
//     boost::split(mes, mes_get, boost::is_any_of("."));
//     for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
//         if ((*i)->get_number()==std::stoi(mes[1])){

//             (*i)->change_x(std::stoi(mes[2]));
//             (*i)->change_y(std::stoi(mes[3]));
//             (*i)->change_destx(std::stoi(mes[4]));
//             (*i)->change_desty(std::stoi(mes[5]));
//             (*i)->reset_havechanged();
//         }
//     }
// }

// void Map::decode_controlpoints(std::string mes_get){
//     std::vector<std::string> mes;
//     boost::split(mes, mes_get, boost::is_any_of("."));
//     for (std::list<Controlpoint*>::iterator i = controlpoints.begin(); i != controlpoints.end(); i++) {
//         if ((*i)->get_number()==std::stoi(mes[1])){
//             (*i)->change_owner(std::stoi(mes[2]));
//             (*i)->change_tgot(std::stoi(mes[3]));
//             (*i)->change_ttoget(std::stoi(mes[4]));
//             (*i)->reset_havechanged();
//         }
//     }
// }

// void Map::decode_spells(std::string mes_get){
//     std::vector<std::string> mes;
//     boost::split(mes, mes_get, boost::is_any_of("."));
// //not sure what changes in spell class mean; spells don't have number to identify and iterate
// } 