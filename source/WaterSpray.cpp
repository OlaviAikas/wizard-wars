#include "../headers/Spray.hpp"
#include "../headers/WaterSpray.hpp"
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>



WaterSpray::WaterSpray(int start_x, int start_y, float dir_x, float dir_y) 
            : Spray::Spray(start_x, start_y, dir_x, dir_y, 100, 100, false) {
    damage = 20;
    sprite = al_load_bitmap("resources/waveSpray.bmp");
    ticks = 0; //Count time 
}

int WaterSpray::get_damage() {
    return damage;
}

void WaterSpray::draw(int camera_x, int camera_y) {
    typedef struct ALLEGRO_MOUSE_STATE ALLEGRO_MOUSE_STATE;
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    float angle = atan2(state.y - y,state.x-x);//-pi/10
    int bitmapw = al_get_bitmap_width(sprite);
    int bitmaph = al_get_bitmap_height(sprite);
    al_draw_scaled_rotated_bitmap(this->sprite,0,bitmaph/2, x -camera_x, y - camera_y,4,2, angle,0);
    ticks += 3;
    if (ticks>100) {
        this->garbage_collect = true;
    };
}

void WaterSpray::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        other.knockback(300*dir_x,300*dir_y);
        // Set garbage_collect to true iif other is not a Player?
        this->hit_animation = true;
        this->noclip = true;}
}