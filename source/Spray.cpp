#include "../headers/Spray.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Player.hpp"
#include "../headers/Map.hpp"
#include <math.h>
#include <iostream>

Spray::Spray(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip, Map* &map)
        : Spell(start_x,  start_y,  dir_x,  dir_y, 30, 50, noclip) {
    // this->number = number;
    this->hit_animation=false;
    int lifetime = 2;
    int range = 3;
    bool hit = false;
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
 }
 



void Spray::draw(int camera_x, int camera_y) { };