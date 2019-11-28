#include "../headers/HUDobject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

HUDobject::HUDobject(int x, int y, int sx, int sy) {
    this->x = x;
    this->y = y;
    this->sx = sx;
    this->sy = sy;
}

void HUDobject::draw() {
    al_draw_rectangle(x, y, x + sx, y + sy, al_map_rgb(0, 0, 0), 0);
}