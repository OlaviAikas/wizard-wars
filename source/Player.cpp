//#define DEBUG_MODE
#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <list>
#define BASE_HEALTH 20
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
    this->drawsprite=true;
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
    if (amount >= hit_points) {
        hit_points = 0;
        std::cout << "The player at " << this << " is really dead" << std::endl;
    } else {
        hit_points -= amount;
        std::cout << "New HP " << hit_points << std::endl;
    }
}

void Player::die() {
    // potentially only if server
    // teleport_to(spawn_point)
    // set_health_to(BASE_HEALTH)
}

void Player::on_collision(MapObject &other) {
    if (not other.get_noclip()) {
        dest_x=lastgoodposx;
        dest_y=lastgoodposy;
    }
}

void Player::move() {
#ifdef DEBUG_MODE
    std::cout << "Moving Player at " << this << std::endl;
#endif
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
}

bool Player::get_drawsprite() {
    return this->drawsprite;
}

void Player::draw(int camera_x, int camera_y) {
    if (this->drawsprite) {
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
    }
    else {
     }; 
    };
