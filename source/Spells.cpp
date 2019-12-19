#include "../headers/Spells.hpp"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>


Spell::Spell(int id, int x, int y, float dir_x, float dir_y, int width, int height, bool noclip) : MapObject::MapObject(x, y, width, height, noclip) {
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->id = id;
    this->havechanged = false;
}


void Spell::draw(int camera_x, int camera_y) { std::cout << "hellods" << std::endl; };
void Spell::move() { std::cout << "helloms" << std::endl; havechanged = true;};
bool Spell::get_havechanged(){
    this->havechanged 
}

float Spell::get_dir_x(){
    return dir_x;
}
float Spell::get_dir_y(){
    return dir_y;
}
/*
int Spell::get_damage() {
    return damage;
}

int Spell::get_healing() {
    return healing;
}

void Spell::on_collision(MapObject &other) {
    // TODO
    // if (this->noclip || other.get_noclip()) {return;}
    std::cout << "colliding Spell at " << this << " with MapObject at " << &other << std::endl;
}

// void Arrow::draw(int mouse_x, int mouse_y) {
// //     float x1 = i->getX() + (i->getWidth() / 2);
// //     float y1 = i->getY() + (i->getHeight() / 2);

// //     float x2 = screenCentreX;
// //     float y2 = ScreenCentreY;

// //     float dx = x2 - x1;
// //     float dy = y2 - y1;
// //     float hypotSquared = (dx * dx) + (dy * dy);
// //     float hypot = sqrt(hypotSquared);

// //     float unitX = dx / hypot;
// //     float unitY = dy / hypot;

// //     float rayX = x2 - view->getViewportX();
// //     float rayY = y2 - view->getViewportY();
// //     float arrowX = 0;
// //     float arrowY = 0;

// //     bool posFound = false;
// //     while(posFound == false)
// //     {
// //          rayX += unitX;
// //          rayY += unitY;

// //          if(rayX <= 0 ||
// //              rayX >= screenWidth ||
// //              rayY <= 0 ||
// //              rayY >= screenHeight)
// //          {
// //              arrowX = rayX;
// //              arrowY = rayY;
// //              posFound = true;
// //          }
// //  }

// //  al_draw_bitmap(sprite, arrowX - spriteWidth, arrowY - spriteHeight, 0);
// //  }

    
//  }

void Spell::draw(int camera_x, int camera_y) {
    al_draw_circle(x - camera_x, y - camera_y, 30, al_map_rgb_f(1, 0, 1), 2);
}

Projectile::Projectile(int start_x, int start_y, int width, int height, bool noclip, int damage, int healing) : Spell::Spell( start_x,  start_y,  width,  height, noclip,  damage,  healing) {
    this->dest_x = start_x;
    this->dest_y = start_y;
    // this->number = number;
}

// short Projectile::get_number() {
//     return this->number;
// }

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
*/