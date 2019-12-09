#include "../headers/Minimap.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <list>
#include <cmath>
#include "../headers/Player.hpp"
#include <iostream>

Minimap::Minimap(const char* name, int win_x, int win_y)
     : HUDobject(win_x * 0.025, win_y - ((win_x * 0.2 * 9) / 16) -  win_x * 0.025, win_x * 0.2, (win_x * 0.2 * 9) / 16, win_y * 0.005) {
    this->map = al_load_bitmap(name);
}

void Minimap::draw(std::list<Player*> players) {
    al_draw_scaled_bitmap(map, 0, 0, al_get_bitmap_width(map), al_get_bitmap_height(map),
    x, y, sx, sy, 0);
    al_draw_rectangle(x, y, x + sx, y + sy, al_map_rgb(0, 0, 0), border);
    for (std::list<Player*>::iterator i = players.begin(); i != players.end(); i++) {
        double pxr = ((double) (*i)->get_x()) / al_get_bitmap_width(map);
        double pyr = ((double) (*i)->get_y()) / al_get_bitmap_height(map);
        if ((*i)->get_team()) {
            al_draw_filled_circle(x + round(sx*pxr), y + round(sy*pyr), 5, al_map_rgb(0, 0, 255));
        } else {
            al_draw_filled_circle(x + round(sx*pxr), y + round(sy*pyr), 5, al_map_rgb(255, 0, 0));
        }
    }
}