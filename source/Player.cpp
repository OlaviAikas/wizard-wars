#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
// add ressource sprite into the input of the class (or multiple for animations)
Player::Player(int start_x, int start_y, int number, ALLEGRO_BITMAP*[13] sprites, bool healthshow) : MapObject(start_x, start_y, 64, 64, false) {
    this->dx = 0;
    this->dy = 0;
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->team = number; //team
		this->speed = 20;
		this->sprites = sprites// path? + do we store it in private for better practice?
		this->count = 0; //keeps the frame count
		this-> health = 100;
		this-> healthshow = healthshow;
		this-> damaged = 0;
}

short Player::get_number() {
    return this->number;
}

void Player::move() {
    if (this->x <= dest_x) {
        this->x = this->x + speed;
    }
    if (this->x >= dest_x) {
        this->x = this->x - speed;
    }
    if (this->y <= dest_y) {
        this->y = this->y + speed;
    }
    if (this->y >= dest_y) {
        this->y = this->y - speed;
    }
}

void Player::set_dest(int dest_x, int dest_y) {
    this->dest_x = dest_x;
    this->dest_y = dest_y;
}

void Player::update_tick(){
	this->count = this->count+1
}

void Player::onhit(){
	this->damaged = 1
	this->number = 0 //reset tick count
}

void Player::draw(int camera_x, int camera_y) {

	//Code to take care of walking animation
	if (this -> dest_x == this-> x && this-> dest_y == this-> y){ //This means that the character is not moving
		if (this->count % 60 < 20) {
			al_draw_bitmap(sprites*[0], x - camera_x, y - camera_y);
		}
		if (this->count % 60 < 40) {
			al_draw_bitmap(sprites*[1], x - camera_x, y - camera_y);
		}
		else {
			al_draw_bitmap(sprites*[2], x - camera_x, y - camera_y);
		}
	}
		if (dest_x > x) {//walking right animation
			if (this->count % 80 < 20) {
				al_draw_bitmap(sprites*[3], x - camera_x, y - camera_y);
			}
			if (this->count % 80 < 40) {
				al_draw_bitmap(sprites*[4], x - camera_x, y - camera_y);
			}
			if (this->count % 80 < 60) {
				al_draw_bitmap(sprites*[5], x - camera_x, y - camera_y);
			}
			else {
				al_draw_bitmap(sprites*[6], x - camera_x, y - camera_y);
			}
		}
		if (dest_x < x) {//walking left animation
			if (this->count % 80 < 20) {
				al_draw_bitmap(sprites*[7], x - camera_x, y - camera_y);
			}
			if (this->count % 80 < 40) {
				al_draw_bitmap(sprites*[8], x - camera_x, y - camera_y);
			}
			if (this->count % 80 < 60) {
				al_draw_bitmap(sprites*[9], x - camera_x, y - camera_y);
			}
			else {
				al_draw_bitmap(sprites*[10], x - camera_x, y - camera_y);
			}
		}

		/*if (this->healthshow == 1) {
			if (this->damaged == 1){ //Health bar
				al_draw_filled_rectangle(x-22 - camera_x, y+50 - camera_y,x+22 - camera_x,y+38,RGB(255,0,0) - camera_y);
				al_draw_filled_rectangle(x-22 - camera_x, y+50 - camera_y,x - camera_x + (44*health)/100,y+38,RGB(0,255,0) - camera_y);
				al_draw_bitmap(sprites*[12], x - camera_x, y - camera_y);

			}
		}
		*/

		//Code for the damaged animation

	}
