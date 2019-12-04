#include "../headers/Spells.hpp"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>


Spell::Spell(int x, int y, int dir_x, int dir_y, bool noclip) : MapObject::MapObject(x, y, width, height, noclip) {
    this->dir_x = dir_x;
    this->dir_y = dir_y;
}

void Spell::draw(int camera_x, int camera_y) { };
void Spell::move() { };


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

//void Spell::draw(int spell_x, int spell_y) {
//    al_draw_circle(spell_x, spell_y, 30, al_map_rgb_f(1, 0, 1), 2);
//}
