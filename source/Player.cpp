//#define DEBUG_MODE
#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <list>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

Player::Player(int start_x, int start_y, short number,int team) : MapObject(start_x, start_y, 64, 64, false) {
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->team = team;
    this->lastgoodposx=start_x;
    this->lastgoodposy=start_y;
	this->sprites0 = al_load_bitmap("resources/player1.bmp");
    this->sprites1 = al_load_bitmap("resources/player1walk.bmp");
	this->sprites2 = al_load_bitmap("resources/player2.bmp");
	this->sprites3 = al_load_bitmap("resources/player2walk.bmp");
	this->sprites4 = al_load_bitmap("resources/player3.bmp");
	this->sprites5 = al_load_bitmap("resources/player3walk.bmp");
	this->sprites6 = al_load_bitmap("resources/player4.bmp");
	this->sprites7 = al_load_bitmap("resources/player4walk.bmp");

    this->speed = 10;
    this->count = 0; //keeps the frame count
    this->damaged = 0;
    this->respawn_timer = 0;
    this->team = team;
    this->havechanged = false;
    this->status_effect_timeout_frozen = 0;
    this->status_effect_timeout_invisible = 0;
    this->prevent_movement = false;
    this->drawsprite = true;
    this->spawnable = true;

}

Player::~Player() {
    al_destroy_bitmap(sprites0);
    al_destroy_bitmap(sprites1);
    al_destroy_bitmap(sprites2);
    al_destroy_bitmap(sprites3);
    al_destroy_bitmap(sprites4);
    al_destroy_bitmap(sprites5);
    al_destroy_bitmap(sprites6);
    al_destroy_bitmap(sprites7);
}

int Player::get_hit_points() {
    return hit_points;
}

int Player::get_team() {
    return this->team;
}

int Player::get_id() {
    return this->team;
}

void Player::hit(int amount) {
    hit_points -= amount;
    std::cout << "New HP " << hit_points << std::endl;
    if (hit_points<0){
        hit_points=0;}
    if (hit_points>=base_health){
        hit_points=base_health;
    }
}

void Player::die() {
    // potentially only if server
    set_x(curspawn1);
    set_y(curspawn2);
    this->dest_x=this->x;
    this->dest_y=this->y;
    this->old_x=this->x;
    this->old_y=this->y;
    this->respawn_timer=0;
    this->noclip=true;
    this->dead = true;
}

void Player::on_collision(MapObject &other) {
    std::cout << "collision" << std::endl;
    if (not other.get_noclip()) {
        dest_x=lastgoodposx;
        dest_y=lastgoodposy;
    }
}

short Player::get_number() {
    return this->number;
}


int Player::get_x(){
    return lastgoodposx;
}
int Player::get_y(){
    return lastgoodposy;
}
int Player::get_dest_x(){
    return dest_x;
}
int Player::get_dest_y(){
    return dest_y;
}
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

void Player::change_spawnable(bool con){
    this->spawnable = con;
}

bool Player::check_dead(){
    return dead;
}

void Player::change_curspawn(int spawn1, int spawn2){
    this->curspawn1 = spawn1;
    this->curspawn2 = spawn2;
};


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
    if (!this->prevent_movement) {
        this->dest_x = dest_x;
        this->dest_y = dest_y;
        this->havechanged = true;
    }
}

int Player::get_next_x(){
	int dx = dest_x - x;
	int dy = dest_y - y;
	int n2 = round(sqrt(dx*dx + dy*dy));
	int nx = round(x + dx * speed / n2);
	return nx;
}

int Player::get_next_y(){
	  int dy = dest_y - y;
	  int dx = dest_x - x;
	  int n2 = round(sqrt(dx*dx + dy*dy));
	  int ny = round(y + dy * speed / n2);
	  return ny;
}

int Player::get_speed(){
	return this->speed;
}

void Player::onhit(){
	this->damaged = 1;
	this->count = 0; //reset tick count
}

void Player::status_effect_invisible() {\
    this->set_dest(this->x,this->y);
    this->drawsprite = false;
    this->status_effect_timeout_invisible = this->count + 3; // 3 frame cooldown on invisibility, modify as needed
}

void Player::status_effect_frozen() {
    this->prevent_movement = true;
    this->status_effect_timeout_frozen = this->count + 30;  // The zone freezes a player for 30 frames, aka it takes 30 frames for the ice to melt
}

void Player::draw(int camera_x, int camera_y) {

    // -- Begin status effect logic --
    if(!this->drawsprite && this->count > this->status_effect_timeout_invisible) { // 3 frame cooldown on invisibility, modify as needed
        // this->status_effect_timer = 0;
        this->drawsprite = true;
    }
    if(this->prevent_movement && this->count > this->status_effect_timeout_frozen) {
        // this->status_effect_timer = 0;
        this->prevent_movement = false;
    }
    // -- End status effect logic --

    if (this->drawsprite && this->hit_points>0) {
        al_draw_filled_rectangle(x-camera_x, y-40-camera_y,x+50-camera_x,y-45-camera_y, al_map_rgb(255,0,0));
		al_draw_filled_rectangle(x-camera_x, y-40-camera_y,x-camera_x + 50*(hit_points)/100,y-45-camera_y, al_map_rgb(0,255,0));
        this->count = this->count + 1; // The draw function is called at every frame, we keep track of frames
        //Code to take care of walking animation
        if (this -> dest_x == this-> x && this-> dest_y == this-> y){ //This means that the character is not moving
            if (this->count % 40 < 20) {
                al_draw_bitmap(this-> sprites0, x - camera_x, y - camera_y, 0);
            } else {
                al_draw_bitmap(this-> sprites1, x - camera_x, y - camera_y, 0);
            }
        }
        else if (dest_x > x) {//walking right animation
            if (this->count % 20 < 10) {
                al_draw_bitmap(this->sprites6, x - camera_x, y - camera_y, 0);
            }
            else {
                al_draw_bitmap(this->sprites7, x - camera_x, y - camera_y, 0);
            }
        }
        else if (dest_x <= x) {//walking left animation
            if (this->count % 20 < 10) {
                al_draw_bitmap(this->sprites4, x - camera_x, y - camera_y, 0);
            }
            else {
                al_draw_bitmap(this->sprites5, x - camera_x, y - camera_y, 0);
            }
        }
    } else if (this->hit_points <= 0) { //Do the counter for respawn and respawn when time
        respawn_timer+=1;
        set_x(curspawn1);
        set_y(curspawn2);
        if (respawn_timer>=120 && spawnable){
            this->noclip=false;
            this->hit_points=this->base_health;
            this->dead = false;
        }
    }
}

bool Player::get_havechanged(){
    return this->havechanged;
}

void Player::reset_havechanged(){
    this->havechanged=false;
}

std::string Player::encode_player(){
    //implement it as soon as Damien finished modifying player
}