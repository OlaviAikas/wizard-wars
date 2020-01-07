//#define DEBUG_MODE
#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <list>
#include <allegro5/allegro.h>

Player::Player(int start_x, int start_y, short number,int team) : MapObject(start_x, start_y, 64, 64, false) {
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->team = team;
    this->lastgoodposx=start_x;
    this->lastgoodposy=start_y;
	this->sprites0 = al_load_bitmap("resources/Sprite-0002.bmp");
    this->sprites1 = al_load_bitmap("resources/Sprite-0003.bmp");
	this->sprites2 = al_load_bitmap("resources/Sprite-0004.bmp");
	this->sprites3 = al_load_bitmap("resources/Sprite-0005.bmp");
	this->sprites4 = al_load_bitmap("resources/Sprite-0006.bmp");
	this->sprites5 = al_load_bitmap("resources/Sprite-0007.bmp");
	this->sprites6 = al_load_bitmap("resources/Sprite-0008.bmp");
	this->sprites7 = al_load_bitmap("resources/Sprite-0009.bmp");
	this->sprites8 = al_load_bitmap("resources/Sprite-0010.bmp");
	this->sprites9 = al_load_bitmap("resources/Sprite-0011.bmp");
	this->sprites10 = al_load_bitmap("resources/Sprite-0012.bmp");
    this->speed = 20;
    this->count = 0; //keeps the frame count
    this->health = 100;
    this->damaged = 0;
    this->time = 0;
    this->team = team;
    this->havechanged = false;
}

Player::~Player() {
    al_destroy_bitmap(sprites0);
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
    this->time=0; //what is time here?
    this->noclip=true;
}

void Player::on_collision(MapObject &other) {
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

int Player::get_next_x(){
	int dx = dest_x - x;
	int dy = dest_y - y;
	int n2 = round(sqrt(dx*dx + dy*dy));
	x = round(x + dx * speed / n2);
	return x;
}

int Player::get_next_y(){
	  int dy = dest_y - y;
	  int dx = dest_x - x;
	  int n2 = round(sqrt(dx*dx + dy*dy));
	  y = round(y + dy * speed / n2);
	  return y;
}

void Player::onhit(){
	this->damaged = 1;
	this->count = 0; //reset tick count
}

void Player::draw(int camera_x, int camera_y) {
    if (this->drawsprite) {
        if (this->hit_points>0){
            this->count = this->count + 1; // The draw function is called at every frame, we keep track of frames

            //Code to take care of walking animation
            if (this -> dest_x == this-> x && this-> dest_y == this-> y){ //This means that the character is not moving
                if (this->count % 160 < 40) {
                    al_draw_bitmap(this-> sprites0, x - camera_x, y - camera_y, 0);
                } else if (this->count % 160 < 80) {
                    al_draw_bitmap(this-> sprites1, x - camera_x, y - camera_y, 0);
                } else if (this->count % 160 < 120) {
                    al_draw_bitmap(this-> sprites2, x - camera_x, y - camera_y, 0);
                } else {
                    al_draw_bitmap(this-> sprites1, x - camera_x, y - camera_y, 0);
                }
            }
            else if (dest_x > x) {//walking right animation
                if (this->count % 160 < 40) {
                    al_draw_bitmap(this->sprites0, x - camera_x, y - camera_y, 0);
                }
                else if (this->count % 160 < 80) {
                    al_draw_bitmap(this->sprites3, x - camera_x, y - camera_y, 0);
                }
                else if (this->count % 160 < 120) {
                    al_draw_bitmap(this->sprites4, x - camera_x, y - camera_y, 0);
                }
                else {
                    al_draw_bitmap(this->sprites5, x - camera_x, y - camera_y, 0);
                }
            }
            else if (dest_x <= x) {//walking left animation
                if (this->count % 160 < 20) {
                    al_draw_bitmap(this->sprites0, x - camera_x, y - camera_y, 0);
                }
                else if (this->count % 160 < 80) {
                    al_draw_bitmap(this->sprites6, x - camera_x, y - camera_y, 0);
                }
                else if (this->count % 160 < 120) {
                    al_draw_bitmap(this->sprites7, x - camera_x, y - camera_y, 0);
                }
                else {
                    al_draw_bitmap(this->sprites8, x - camera_x, y - camera_y, 0);
                }
            }
        }
        else{ //Do the counter for respawn and respawn when time
            time+=1;
            if (time>=120){
                this->noclip=false;
                this->hit_points=health;
            }
        }
    }
}


		/*if (this->healthshow == 1) {
			if(healthshow == 1){
				if (this->damaged == 1){ //Health bar only shows when you are being damaged
					al_draw_filled_rectangle(x-22 - camera_x, y+50 - camera_y,x+22 - camera_x,y+38,RGB(255,0,0) - camera_y);
					al_draw_filled_rectangle(x-22 - camera_x, y+50 - camera_y,x - camera_x + (44*health)//100,y+38,RGB(0,255,0) - camera_y);
					al_draw_bitmap(sprites*[12], x - camera_x, y - camera_y);
					if (this-> count > 15){
						this->damaged == 0;
					}
			}
		}
		*/

		//Code for the damaged animation


bool Player::get_havechanged(){
    this->havechanged ;
}

void Player::reset_havechanged(){
    this->havechanged=false;
}
