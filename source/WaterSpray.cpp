#include "../headers/Spray.hpp"
#include "../headers/WaterSpray.hpp"
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>



WaterSpray::WaterSpray(int start_x, int start_y, float dir_x, float dir_y,Map* &map) 
            : Spray::Spray(start_x, start_y, dir_x, dir_y, 100, 100, false, map) {
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
    float angle = atan2(x - state.x,state.y-y);//-pi/10
    al_draw_scaled_rotated_bitmap(this->sprite,0,0, x - camera_x, y - camera_y,4,2, angle,0);
    ticks += 3;
    if (ticks>200) {
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