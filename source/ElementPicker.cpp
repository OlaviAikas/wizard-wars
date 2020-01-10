#include "../headers/ElementPicker.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

ElementPicker::ElementPicker(int x, int y, int sx, int sy, int* element) : HUDobject(x, y, sx, sy, 0) {
    this->element = element;
    sprite1 = al_load_bitmap("resources/elementLife.bmp");
    sprite2 = al_load_bitmap("resources/elementShield.bmp");
    sprite3 = al_load_bitmap("resources/elementFire.bmp");
    sprite4 = al_load_bitmap("resources/elementWater.bmp");
    sprite5 = al_load_bitmap("resources/elementIce.bmp");
    sprite6 = al_load_bitmap("resources/elementRock.bmp");
}

void ElementPicker::draw() {
    if (*element == 1) {
        al_draw_scaled_bitmap(this->sprite1,0,0,32,32, x,y,64,64,0);
        //al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(130, 119, 105));
    } else if (*element == 2) {
        al_draw_scaled_bitmap(this->sprite2,0,0,32,32, x,y,64,64,0);
        //al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(122, 255, 248));
    } else if (*element == 3) {
        al_draw_scaled_bitmap(this->sprite3,0,0,32,32, x,y,64,64,0);
        //al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(252, 40, 40));
    } else if (*element == 5) {
        al_draw_scaled_bitmap(this->sprite4,0,0,32,32, x,y,64,64,0);
        //al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(122, 255, 248));
    } else if (*element == 7) {
        al_draw_scaled_bitmap(this->sprite5,0,0,32,32, x,y,64,64,0);
        //al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(247, 247, 84));
    } else {
        al_draw_scaled_bitmap(this->sprite6,0,0,32,32, x,y,64,64,0);
        //al_draw_filled_circle(x + sx/2, y + sy/2, (sx + sy)/4, al_map_rgb(234, 234, 234));
    }
}