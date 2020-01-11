#pragma once
#include "HUDobject.hpp"
#include <allegro5/allegro5.h>

class ElementPicker : public HUDobject {
    public:
        ElementPicker(int x, int y, int sx, int sy, int* element);
        ~ElementPicker();
        void draw();

    private:
        int* element;
        ALLEGRO_BITMAP* sprite1;
        ALLEGRO_BITMAP* sprite2;
        ALLEGRO_BITMAP* sprite3;
        ALLEGRO_BITMAP* sprite4;
        ALLEGRO_BITMAP* sprite5;
        ALLEGRO_BITMAP* sprite6;
};