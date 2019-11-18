#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <list>

Player::Player(int start_x, int start_y, int number) : MapObject(start_x, start_y, 64, 64, false) {
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

//void Player::move() {
//    if (this->x <= dest_x) {
//        this->x = this->x + speed;
//    }
//    if (this->x >= dest_x) {
//        this->x = this->x - speed;
//    }
//    if (this->y <= dest_y) {
//        this->y = this->y + speed;
//    }
//    if (this->y >= dest_y) {
//        this->y = this->y - speed;
//    }
//}

void Player::move() {
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
        y = dest_y;
    } else if(abs(y - dest_y) >= speed) {
        int dx = dest_x - x;
        int dy = dest_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = dest_x;
        y = int (y + dy * speed / n2);
    } else if (x == dest_x) {
        y = dest_y;
    } else if (y == dest_y) {
        x = dest_x;
    } else if (x != dest_x && y != dest_y) {
        old_x = x;
        old_y = y;
        x = dest_x;
        y = dest_y;
    }
}

void Player::set_dest(int dest_x, int dest_y) {
    this->dest_x = dest_x;
    this->dest_y = dest_y;
}
