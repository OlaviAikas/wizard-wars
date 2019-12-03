#pragma once
#include "../headers/Projectile.hpp"
#include <math.h>


Projectile::Projectile(int start_x, int start_y, int dir_x, int dir_y, bool noclip, int speed) : Spell::Spell( start_x,  start_y,  dir_x,  dir_y) {
    this->dest_x = start_x;
    this->dest_y = start_y;
    this->target_x = dir_x;
    this->target_y = dir_y;
    this->speed = speed;
    // this->number = number;
}

// short Projectile::get_number() {
//     return this->number;
// }


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