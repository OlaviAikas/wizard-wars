#include "../headers/ElementPicker.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

ElementPicker::ElementPicker(int x, int y, int sx, int sy, int* element) : HUDobject(x, y, sx, sy, 0) {
    this->element = element;
}

void ElementPicker::draw() {
    if (*element == 11) {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(130, 119, 105));
    } else if (*element == 7) {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(122, 255, 248));
    } else if (*element == 3) {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(252, 40, 40));
    } else if (*element == 11) {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(122, 255, 248));
    } else if (*element == 2) {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(247, 247, 84));
    } else if (*element == 1) {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(117, 249, 87));
    } else {
        al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(234, 234, 234));
    }
}