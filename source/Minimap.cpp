#include "../headers/Minimap.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

Minimap::Minimap(const char* name, int win_x, int win_y) : HUDobject(win_x, win_y) {
    this->map = al_load_bitmap(name);
}

void Minimap::draw() {
    al_draw_scaled_bitmap(map, 0, 0, al_get_bitmap_width(map), al_get_bitmap_height(map),
    x, y, sx, sy, 0);
}