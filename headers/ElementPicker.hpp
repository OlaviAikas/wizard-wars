#pragma once
#include "HUDobject.hpp"

class ElementPicker : public HUDobject {
    public:
        ElementPicker(int x, int y, int sx, int sy, int* element);
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