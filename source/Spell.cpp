// Original Wanqi's file

#include "../headers/Spell.hpp"
#include "../headers/Player.hpp"
#include "../headers/MapObject.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <list>

Projectile::Projectile(int start_x, int start_y, int number) : MapObject(start_x, start_y, 20, 20, false) {
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->number = number;
}

short Projectile::get_number() {
    return this->number;
}

void Projectile::on_collision(MapObject other) {
    if (not other.get_noclip()) {
        dest_x = x;
        dest_y = y;
    }
}

void Projectile::move() {
    if (abs(x - target_x) >= speed && abs(y - target_y) >= speed) {
        int dx = target_x - x;
        int dy = target_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = round(x + dx * speed / n2);
        y = round(y + dy * speed / n2);
    } else if (abs(x - target_x) >= speed) {
        int dx = target_x - x;
        int dy = target_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = round(x + dx * speed / n2);
        y = round(y + dy * speed / n2);
    } else if(abs(y - target_y) >= speed) {
        int dx = target_x - x;
        int dy = target_y - y;
        int n2 = round(sqrt(dx*dx + dy*dy));
        old_x = x;
        old_y = y;
        x = round(x + dx * speed / n2);
        y = round(y + dy * speed / n2);
    } else if (x != target_x && y != target_y) {
        old_x = x;
        old_y = y;
        x = target_x;
        y = target_y;
    }
};

void Projectile::set_target(int target_x, int target_y) {
    this->target_x = target_x;
    this->target_y = target_y;
};

