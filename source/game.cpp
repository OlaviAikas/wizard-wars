#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <list>
#include <iostream>
#include "../headers/Map.hpp"
#include "../headers/Camera.hpp"
#include "../headers/MapObject.hpp"
#include "../headers/Player.hpp"

void must_init(bool, const char);

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main(int argc, char **argv)
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY* disp = al_create_display(3200, 1800); //Change this resolution to change window size
    must_init(disp, "display");
    ALLEGRO_BITMAP* buffer = al_create_bitmap(1920, 1080); //Do not touch

    float windowWidth = al_get_display_width(disp);
    float windowHeight = al_get_display_height(disp);
    float screenWidth = 1920; //Do not touch
    float screenHeight = 1080;

    float sx = windowWidth / screenWidth;
    float sy = windowHeight / screenHeight;
    float scale = std::min(sx, sy);

    float scaleW = screenWidth * scale;
    float scaleH = screenHeight * scale;
    float scaleX = (windowWidth - scaleW) / 2;
    float scaleY = (windowHeight - scaleH) / 2;

    must_init(al_init_primitives_addon(), "primitives");

    must_init(al_init_image_addon(), "Image addon");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    short client_number = 1;
    Map* map = new Map("resources/map.bmp");
    map->players.push_back(Player(400, 400, 1));
    map->players.push_back(Player(100, 100, 2));
    Camera camera = Camera(0, 0);
    std::list<Player>::iterator pit = map->fetch_pit(client_number);

    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));


    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                if (key[ALLEGRO_KEY_A])
                    camera.move_x(-20);

                if (key[ALLEGRO_KEY_D])
                    camera.move_x(20);

                if (key[ALLEGRO_KEY_W])
                    camera.move_y(-20);

                if (key[ALLEGRO_KEY_S])
                    camera.move_y(20);
                
                if (key[ALLEGRO_KEY_U])
                    
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                map->move_list(map->players);
                map->check_collisions();

                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button == 2) {
                    pit->set_dest(event.mouse.x / sx + camera.get_x(), event.mouse.y / sy + camera.get_y());
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

	        default:
		        break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));

            map->draw_map(camera.get_x(), camera.get_y());

            map->draw_list(map->players, camera.get_x(), camera.get_y());

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }

    delete map;
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
