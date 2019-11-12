#include "../headers/MapObject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

MapObject::MapObject(int x, int y, int width, int height, bool noclip) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->noclip = noclip;
}

int MapObject::get_x() {
    return x;
}

int MapObject::get_y() {
    return y;
}

void MapObject::draw(int camera_x, int camera_y) {
    al_draw_filled_rectangle(x - camera_x, y - camera_y, x + width - camera_x, y + height - camera_y, al_map_rgb(255, 0, 0));
}