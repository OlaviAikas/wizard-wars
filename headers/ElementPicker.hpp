#pragma once
#include "HUDobject.hpp"

class ElementPicker : public HUDobject {
    public:
        ElementPicker(int x, int y, int sx, int sy);
        void set_element(int new_element);
        int get_element();
        void draw();

    private:
        int element;
};