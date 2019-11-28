#include "../headers/Spells.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>

Spell::Spell(int x, int y, int width, int height, bool noclip, int damage, int healing, int target_x, int target_y) : MapObject::MapObject(x, y, width, height, noclip) {
    this->damage = damage;
    this->healing = healing;
    this->target_x = target_x;
    this->target_y = target_y;
}

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

void Arrow::draw(int mouse_x, int mouse_y) {
//     float x1 = i->getX() + (i->getWidth() / 2);
//     float y1 = i->getY() + (i->getHeight() / 2);

//     float x2 = screenCentreX;
//     float y2 = ScreenCentreY;

//     float dx = x2 - x1;
//     float dy = y2 - y1;
//     float hypotSquared = (dx * dx) + (dy * dy);
//     float hypot = sqrt(hypotSquared);

//     float unitX = dx / hypot;
//     float unitY = dy / hypot;

//     float rayX = x2 - view->getViewportX();
//     float rayY = y2 - view->getViewportY();
//     float arrowX = 0;
//     float arrowY = 0;

//     bool posFound = false;
//     while(posFound == false)
//     {
//          rayX += unitX;
//          rayY += unitY;

//          if(rayX <= 0 ||
//              rayX >= screenWidth ||
//              rayY <= 0 ||
//              rayY >= screenHeight)
//          {
//              arrowX = rayX;
//              arrowY = rayY;
//              posFound = true;
//          }
//  }

//  al_draw_bitmap(sprite, arrowX - spriteWidth, arrowY - spriteHeight, 0);
//  }

    
 }

void Spell::draw(int camera_x, int camera_y) {
    al_draw_circle(x - camera_x, y - camera_y, 30, al_map_rgb_f(1, 0, 1), 2);
}