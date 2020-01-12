#include "../headers/Spray.hpp"
#include "../headers/FireSpray.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <math.h>
#include <list>
#include "../headers/Player.hpp"
#include "../headers/Map.hpp"


FireSpray::FireSpray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map) 
            : Spray::Spray(pit, dxp, dyp, 12, 12, false, mouse_down, map) {
    damage = 1.5;
    sprite = al_load_bitmap("resources/firespray.bmp");
}

FireSpray::~FireSpray() {}
int FireSpray::get_damage() {
    return damage;
}

void FireSpray::draw(int camera_x, int camera_y) {
    float angle = atan2(origin_y - y, origin_x - x) + ALLEGRO_PI;
    int bitmapw = al_get_bitmap_width(sprite);
    int bitmaph = al_get_bitmap_height(sprite);
    float scale = 5;//sqrt((x-origin_x)*(x-origin_x)+(y-origin_y)*(y-origin_y));
    al_draw_scaled_rotated_bitmap(this->sprite,0,bitmaph/2, origin_x - camera_x, origin_y - camera_y,scale,1.5, angle,0);
}
void FireSpray::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->noclip = true;
    }
}

void FireSpray::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        other.hit(this->get_damage());
        this->hit_animation = true;
        this->noclip = true;}
}