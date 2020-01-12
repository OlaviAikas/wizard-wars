#pragma once
#include "Map.hpp"
#include "MapObject.hpp"
#include "Spells.hpp"
#include <list>
#include "Player.hpp"

class Beam: public Spell {
    public:
        Beam(std::list<Player*>::iterator &pit, float* dxp, float* dyp, int width, int height, bool noclip, bool* mouse_down, Map* map);
        virtual ~Beam();

        void move();

        virtual void draw(int camera_x, int camera_y);
    
    protected:
        float range;
        std::list<Player*>::iterator pit;
        int origin_x;
        int origin_y;
        float* dxp;
        float* dyp;
        bool* mouse_down;
        Map* map;
        //bool hitted;
};