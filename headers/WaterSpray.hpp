//Water spray with special functions(knockback)
#pragma once
#include "Spray.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <list>
#include "Player.hpp"
#include "Map.hpp"
class WaterSpray: public Spray {
    public:
        WaterSpray(std::list<Player*>::iterator &pit, float* dxp, float* dyp, bool* mouse_down, Map* map);
        ~WaterSpray();

        int get_damage();

        virtual void on_collision(MapObject &other);

        virtual void draw(int camera_x, int camera_y);

    private:
    ALLEGRO_BITMAP* sprite;
    int damage;
};