#pragma once
#include <allegro5/allegro5.h>
#include <functional>
#include <iostream>

template <typename ...Args> class Button {
    public:
        Button(int loc_x, int loc_y, int span_x, int span_y, ALLEGRO_COLOR color, void (*callback)(Args... args)) {
            this->x = loc_x;
            this->y = loc_y;
            this->span_x = x + span_x;
            this->span_y = y + span_y;
            this->callback = callback;
            this->color = color;
        }

        void mouse_input(int mouse_x, int mouse_y, short &state, short new_state) {
            std::cout << mouse_x << std::endl;
            std::cout<<mouse_y << std::endl ;
            if (mouse_x > x && mouse_x < x + span_x){
                if (mouse_y > y && mouse_y < y + span_y){
                    call_callback(state, new_state);
                }
            }
        }

        void draw() {
            al_draw_filled_rectangle(x, y, span_x, span_y, color);
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
        ALLEGRO_COLOR color;
};