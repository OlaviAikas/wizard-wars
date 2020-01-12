#include "../headers/Spray.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Player.hpp"
#include "../headers/Map.hpp"
#include <math.h>
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <iostream>

Spray::Spray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool* mouse_down, Map* map)
         : Spell((*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp),  (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp),  *dxp,  *dyp, width, height, noclip) {
    // this->number = number;
    this->hit_animation=false;
    int lifetime = 2;
    int range = 3;
    bool hit = false;
    float start_x=(*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp);
    float start_y=(*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp);
    float dx=start_x+dir_x;
    float dy=start_y + dir_y;
    float a = dir_y/dir_x;
    float gam = dy+dx/a;
    float mu1 = (a*a*gam-a*dx+dy+sqrt((a*a*gam+a*dx-dy)*(a*a*gam+a*dx-dy)-(a*a+1)*(dy*dy+dx*dx-2*a*gam*dx+(gam*a)*(gam*a))-2500))/(a*a+1);
    float lam1 = a*gam-a*mu1;
    float mu2 = (a*a*gam-a*dx+dy-sqrt((a*a*gam+a*dx-dy)*(a*a*gam+a*dx-dy)-(a*a+1)*(dy*dy+dx*dx-2*a*gam*dx+(gam*a)*(gam*a))-2500))/(a*a+1);
    float lam2 = a*gam-a*mu2;
    float a1=(lam1-start_x)/(mu1-start_y);
    float a2=(lam2-start_x)/(mu2-start_y);
    float b1=a1*start_x-start_y;
    float b2=a2*start_x-start_y;
    //we have a1x+b1=y, a2x+b2=y, -x/a+gam=y
    for (float i = 1; i <= range; i = i + 0.05) {
        for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {
            for (float k=a2;k<=a1;k=k+0.05) {
                this->x = round(x + k*i*width);
                this->y = round(y + k*i*height);    
                if (*this == **j) {
                    hit = true;
                    break;
                }
            }
        }
    }
    music20 = al_load_sample("resources/spray.wav");
    al_play_sample(music20, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
}


// Spray::Spray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool* mouse_down, Map* map)
//         : Spell((*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp),  (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp),  *dxp,  *dyp, width, height, noclip) {
//     // this->number = number;
//     this->hit_animation=false;
//     range = 1.4;
//     this->pit = pit;
//     this->map = map;
//     this->origin_x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(*dxp);
//     this->origin_y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(*dyp);
//     this->dxp = dxp;
//     this->dyp = dyp;
//     this->mouse_down = mouse_down;
//     bool hit = false;
//     for (float i = 1; i <= range; i = i + 0.05) {
//         std::cout << i << std::endl;
//         // A loop that checks if it collides any player on the map
//         for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {
//             this->x = round(x + (*dxp)*i*width);
//             this->y = round(y + (*dxp)*i*height);    
//             if (*this == **j) {
//                 hit = true;
//                 break;
//             }
//         }
//     if (hit) { break; }
//     }
// };


// Spray::~Spray() { }

void Spray::move() {
    if (!*mouse_down) {
        this->garbage_collect = true;
    }
    float dx = *dxp;
    float dy = *dyp;
    this->x = (*pit)->get_x() + (*pit)->get_width()/2 + (*pit)->get_width()*(dx);
    this->y = (*pit)->get_y() + (*pit)->get_height()/2 + (*pit)->get_height()*(dy);
    this->origin_x = x;
    this->origin_y = y;
    bool hit = false;
    noclip = false;
    for (float i = 1; i <= range; i = i + 0.05) {
        // A loop that checks if it collides any player on the map
        for (std::list<Player*>::iterator j = map->players.begin(); j != map->players.end(); j++) {
            this->x = round(x + (dx)*i*width);
            this->y = round(y + (dy)*i*height);    
            if (*this == **j) {
                hit = true;
                break;
            }
        }
    if (hit) { break; }
    }
}

Spray::~Spray(){
    al_destroy_sample(music20);
}

// void must_init(bool, const char);

void Spray::draw(int camera_x, int camera_y) {
    // must_init(al_init_primitives_addon(), "primitives");
    // must_init(al_init_image_addon(), "Image addon");
    // must_init(al_install_audio(), "Audio addon");
    // must_init(al_init_acodec_addon(), "Audio codecs addon");
    // must_init(al_reserve_samples(16), "reserve samples");
    //ALLEGRO_SAMPLE* music20 = al_load_sample("resources/spray.wav");
    //al_play_sample(music20, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
    // ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 300, 200, ALLEGRO_ALIGN_CENTRE, "Dzooooone");
    //al_destroy_sample(music20);
}
