#include "../headers/MainShield.hpp"
#include <iostream>
#include <math.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <list>

MainShield::MainShield(int start_x, int start_y, float dir_x, float dir_y) 
            : Shield::Shield(start_x, start_y, dir_x, dir_y, 16, 16, false) {
    damage = 0;
    sprite = al_load_bitmap("resources/shield0.bmp");
    int time1 = 0;
    music11 = al_load_sample("resources/main_shield.wav");
    if (music11) al_play_sample(music11, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id);
    
}

MainShield::~MainShield(){
    al_destroy_sample(music11);
    al_destroy_bitmap(sprite);
}

int MainShield::get_damage() {
    return damage;
}

    
    



void MainShield::draw(int camera_x, int camera_y) {
    al_draw_filled_rectangle(x - camera_x, y - camera_y, x + width - camera_x, y + height - camera_y, al_map_rgb(255, 255, 100));
    //time1=time1+1;
    //if (time1>30) {
    //    this->garbage_collect = true;
    //}
    //float angle = atan2(dir_y,dir_x);
    //al_draw_scaled_rotated_bitmap(this->sprite,50,5, x - camera_x, y - camera_y,2,2, angle,0);
    time1=time1+1;
    if (time1>30) {
        this->garbage_collect = true;
    }
    float angle = atan2(dir_y,dir_x);
    float bitmapw = al_get_bitmap_width(sprite);
    float bitmaph = al_get_bitmap_height(sprite);
    al_draw_scaled_rotated_bitmap(this->sprite,0,bitmaph/2, x - camera_x, y - camera_y,2,2, angle,0);
}

void MainShield::on_collision(MapObject &other) {
    if (!this->get_garbage_collect() && !this->hit_animation && !other.get_noclip()) {
        this->hit_animation = true;
        this->noclip = true;
        //other.preventhit();
    }
}

std::list<std::list<int>> MainShield::generate_subshield_coordinates() {
    float angle = atan2(dir_y,dir_x);
    //let x, y be the point representing the position of the rotated sprite which was set exactly in the middle of the sprite
    std::list<std::list<int>> result = std::list<std::list<int>>();
    float covered_distance = 0;
    const int height_of_rectangle = 10;
    const int width_of_rectangle = height_of_rectangle * atan(angle);

    //computation to get x and y need to be done
    float dx= x + dir_x;
    float dy= y + dir_y;
    float a = dir_y/dir_x;
    float gam = dy+dx/a;
    float left_x = (a*a*gam-a*dx+dy+sqrt((a*a*gam+a*dx-dy)*(a*a*gam+a*dx-dy)-(a*a+1)*(dy*dy+dx*dx-2*a*gam*dx+(gam*a)*(gam*a))-2500))/(a*a+1);
    float top_y = a*gam-a*left_x;

    //let position_x and position_y be the positions of the vertice at the top

    while (covered_distance < 100) {
        covered_distance += sqrt( pow( height_of_rectangle,2) + pow(width_of_rectangle,2) );
        std::list<int> one_rectangle = std::list<int>();
        //case 1
        if (0 < angle && angle < ALLEGRO_PI/2) {//angle is with respect to the vertical axis
            one_rectangle.push_back(left_x);
            one_rectangle.push_back(top_y);
            one_rectangle.push_back(width_of_rectangle);
            one_rectangle.push_back(height_of_rectangle);
            
            result.push_back(one_rectangle);
            top_y += width_of_rectangle;
            left_x += height_of_rectangle;
        }
        //case 2
        if (ALLEGRO_PI/2 < angle && angle < ALLEGRO_PI) {
            one_rectangle.push_back(left_x-width_of_rectangle);
            one_rectangle.push_back(top_y);
            one_rectangle.push_back(width_of_rectangle);
            one_rectangle.push_back(height_of_rectangle);

            result.push_back(one_rectangle);
            top_y += height_of_rectangle;
            left_x += -width_of_rectangle;
        }
        //case 3
        if (-ALLEGRO_PI < angle && angle < -ALLEGRO_PI/2) {
            one_rectangle.push_back(left_x-width_of_rectangle);
            one_rectangle.push_back(top_y-height_of_rectangle);
            one_rectangle.push_back(width_of_rectangle);
            one_rectangle.push_back(height_of_rectangle);

            result.push_back(one_rectangle);
            top_y += -height_of_rectangle;
            left_x += -width_of_rectangle;
        }
        //case 4
        if (-ALLEGRO_PI/2 < angle && angle < 0) {
            one_rectangle.push_back(left_x);
            one_rectangle.push_back(top_y-height_of_rectangle);
            one_rectangle.push_back(width_of_rectangle);
            one_rectangle.push_back(height_of_rectangle);

            result.push_back(one_rectangle);
            top_y += -height_of_rectangle;
            left_x += width_of_rectangle;
        }
    }
    
    return result;
}