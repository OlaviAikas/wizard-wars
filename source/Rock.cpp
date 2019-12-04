#include "../headers/Rock.hpp"

Rock::Rock(int start_x, int start_y, int dir_x, int dir_y) 
            : Projectile::Projectile(start_x, start_y, dir_x, dir_y, false, 20) {
    this->x = start_x;
    this->y = start_y;
    damage = 10;
    sprite = al_load_bitmap("resources/Projectile.bmp");
}

int Rock::get_damage() {
    return damage;
}

void Rock::draw(int camera_x, int camera_y) {
    al_draw_bitmap(this->sprite, x - camera_x, y - camera_y, 0);
}

void Rock::on_collision(MapObject other) { }
