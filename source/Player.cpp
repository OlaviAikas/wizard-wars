#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>

Player::Player(int start_x, int start_y, int number) : MapObject(start_x, start_y, 64, 64, false) {
    this->dx = 0;
    this->dy = 0;
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->number = number;
}

short Player::get_number() {
    return this->number;
}

void Player::on_collision(MapObject other) {
    if (not other.get_noclip()) {
        dest_x = x;
        dest_y = y;
    }
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
