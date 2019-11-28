#include "../headers/HUDobject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

HUDobject::HUDobject(int win_x, int win_y) {
    this->sx = win_x * 0.2;
    this->sy = (sx * 9) / 16;
    this->x = win_x * 0.025;
    this->y = win_y - sy - x;
}

void HUDobject::draw() {
    al_draw_filled_rectangle(x, y, x + sx, y + sy, al_map_rgb(0, 0, 0));
}