#pragma once
#include <allegro5/allegro5.h>
#include <functional>

class Button {
    public:
        Button(int loc_x, int loc_y, int span_x, int span_y, ALLEGRO_COLOR color);

        void draw();
        void on_click();

    private:
        int x;
        int y;
        int span_x;
        int span_y;
        ALLEGRO_COLOR color;
};