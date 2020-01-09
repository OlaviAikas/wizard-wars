#pragma once
#include "HUDobject.hpp"

class ElementPicker : public HUDobject {
    public:
        ElementPicker(int x, int y, int sx, int sy, int* element);
        void draw();

    private:
        int* element;
};