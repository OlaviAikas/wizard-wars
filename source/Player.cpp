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

void Player::move() {
    if (this->x <= dest_x) {
        this->x = this->x + 10;
    }
    if (this->x >= dest_x) {
        this->x = this->x - 10;
    }
    if (this->y <= dest_y) {
        this->y = this->y + 10;
    }
    if (this->y >= dest_y) {
        this->y = this->y - 10;
    }
}

void Player::set_dest(int dest_x, int dest_y) {
    this->dest_x = dest_x;
    this->dest_y = dest_y;
}
