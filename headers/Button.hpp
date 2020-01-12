#pragma once
#include <allegro5/allegro5.h>
#include <functional>
#include <iostream>

template <typename ...Args> class Button {
    public:
        Button(int loc_x, int loc_y, const char* name, void (*callback)(Args... args)) {
            this->x = loc_x;
            this->y = loc_y;
            this->callback = callback;
            this->image = al_load_bitmap(name);
            this->span_x = al_get_bitmap_width(image);
            this->span_y = al_get_bitmap_height(image);
        }

        void mouse_input(int mouse_x, int mouse_y, Args... args) {
            if (mouse_x > x && mouse_x < x + span_x){
                if (mouse_y > y && mouse_y < y + span_y){
                    call_callback(args...);
                }
            }
        }

        void draw() {
            al_draw_bitmap(image, x, y, 0);
        }
        void on_click();

        void call_callback(Args... args) {
            callback(args...);
        }

    private:
        int x;
        int y;
        int span_x;
        int span_y;
        void (*callback)(Args... args);
        ALLEGRO_BITMAP* image;
};