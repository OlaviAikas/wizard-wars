#include "../headers/HUDobject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

HUDobject::HUDobject(int x, int y, int sx, int sy, int border) {
    this->sx = sx;
    this->sy = sy;
    this->x = x;
    this->y = y;
    this->border = border;
}

HUDobject::~HUDobject() { }

void HUDobject::draw() {
    al_draw_filled_rectangle(x, y, x + sx, y + sy, al_map_rgb(0, 0, 0));
}