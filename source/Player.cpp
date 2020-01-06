//#define DEBUG_MODE
#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <list>
#define BASE_HEALTH 50
#include <allegro5/allegro.h>

Player::Player(int start_x, int start_y, int number, bool team, const char* sprite_name) : MapObject(start_x, start_y, 64, 64, false) {
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->number = number;
    this->hit_points = BASE_HEALTH;
    this->lastgoodposx=start_x;
    this->lastgoodposy=start_y;
    this->sprite = al_load_bitmap(sprite_name);
    this->team = team;
    this->havechanged = false;
}

Player::~Player() {
    al_destroy_bitmap(sprite);
}

int Player::get_hit_points() {
    return hit_points;
}

short Player::get_number() {
    return this->number;
}

bool Player::get_team() {
    return this->team;
}

void Player::hit(int amount) {
    hit_points -= amount;
    std::cout << "New HP " << hit_points << std::endl;
    if (hit_points<0){
        hit_points=0;
    }
}

void Player::die(int* spawn) {
    // potentially only if server
    set_x(*spawn);
    set_y(*(spawn++));
    this->dest_x=this->x;
    this->dest_y=this->y;
    this->old_x=this->x;
    this->old_y=this->y;
    this->time=0;
    this->noclip=true;
}

void Player::on_collision(MapObject &other) {
    if (not other.get_noclip()) {
        dest_x=lastgoodposx;
        dest_y=lastgoodposy;
    }
}
int Player::get_x(){
    return lastgoodposx;
}
int Player::get_y(){
    return lastgoodposy;
}
int Player::get_dest_x(){
    return dest_x;
};
int Player::get_dest_y(){
    return dest_y;
};
void Player::change_x(int x){
    this->lastgoodposx=x;
}
void Player::change_y(int y){
    this->lastgoodposy=y;
}
void Player::change_destx(int destx){
    this->dest_x=destx;
}
void Player::change_desty(int desty){
    this->dest_y=desty;
}

void Player::move() {
#ifdef DEBUG_MODE
    std::cout << "Moving Player at " << this << std::endl;
#endif
    havechanged = true;
    lastgoodposx=x;
    lastgoodposy=y;
    if (abs(x - dest_x) >= speed && abs(y - dest_y) >= speed) {
        int dx = dest_x - x;
        int dy = dest_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = round(x + dx * speed / n2);
        y = round(y + dy * speed / n2);
    } else if (abs(x - dest_x) >= speed) {
        int dx = dest_x - x;
        int dy = dest_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = round(x + dx * speed / n2);
        y = round(y + dy * speed / n2);
    } else if(abs(y - dest_y) >= speed) {
        int dx = dest_x - x;
        int dy = dest_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = round(x + dx * speed / n2);
        y = round(y + dy * speed / n2);
    } else if (x != dest_x && y != dest_y) {
        old_x = x;
        old_y = y;
        x = dest_x;
        y = dest_y;
    } else {
#ifdef DEBUG_MODE
        std::cout << "Player at " << this << " did not move on this frame" << std::endl;
#endif
    }
}

void Player::set_dest(int dest_x, int dest_y) {
    this->dest_x = dest_x;
    this->dest_y = dest_y;
    this->havechanged = true;
    }

void Player::draw(int camera_x, int camera_y) {
    if (this->hit_points>0){
        al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
    }
    else{ //Do the counter for respawn and respawn when time
        time+=1;
        if (time>=120){
            this->noclip=false;
            this->hit_points=BASE_HEALTH;
        }
    }
}

bool Player::get_havechanged(){
    this->havechanged ;
}

void Player::reset_havechanged(){
    this->havechanged=false;
}