#include "../headers/Button.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <functional>

Button::Button(int loc_x, int loc_y, int span_x, int span_y, ALLEGRO_COLOR color) {
    this->x = loc_x;
    this->y = loc_y;
    this->span_x = span_x;
    this->span_y = span_y;
    this->color = color;
}

void Button::draw() {
    al_draw_filled_rectangle(x, y, span_x, span_y, color);
}