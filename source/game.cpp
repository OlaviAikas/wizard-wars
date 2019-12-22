//#define DEBUG_MODE
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <list>
#include <iostream>
#include <cstdlib>
#include "../headers/Map.hpp"
#include "../headers/Camera.hpp"
#include "../headers/MapObject.hpp"
#include "../headers/Player.hpp"
#include "../headers/Button.hpp"
#include "../headers/HUDobject.hpp"
#include "../headers/Minimap.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Projectile.hpp"
#include "../headers/Rock.hpp"
#include <cmath>
#include "../headers/Controlpoint.hpp"

#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Interface.hpp"
#include "../headers/Gamestatus.hpp"



#define KEY_SEEN     1
#define KEY_RELEASED 2

void must_init(bool, const char);
void change_state(short &, short new_state);
void main_menu_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, const float&, const float&);

void game_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, Interface &interface);

void main_menu_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy) {
    //Load what you need to before the loop:
    void (*changeptr)(short &, short new_state);
    changeptr = change_state;
    Button<short &, short>* start_game = new Button<short &, short>(840, 500, 240, 60, al_map_rgb(0, 255, 0), changeptr);
    Button<short &, short>* end_game = new Button<short &, short>(840, 600, 240, 60, al_map_rgb(0, 255, 0), changeptr);

    while(game_status->game_state == 1) {
    al_wait_for_event(queue, &event);
    switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                    game_status->game_state = 0;
                }
                if (key[ALLEGRO_KEY_ENTER]) {
                    start_game->call_callback(game_status->game_state, 2);
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                start_game->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 2);
                end_game->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 0);
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_status->game_state = 0;
                break;
        }
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));
            start_game->draw();
            end_game->draw();

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }
    //delete what you loaded
    delete start_game;
}

void game_loop (Gamestatus* game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer, 
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight,
                    const float &windowWidth, const float &windowHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, Interface &interface) {
    //Load what you need to load
    
    short client_number = 1;
    ALLEGRO_BITMAP* rock_sprite = al_load_bitmap("resources/Projectile.bmp");
    Map* map = new Map("resources/map.bmp", &interface);
    
    map->players.push_back(new Player(900, 900, *(game_status->playerNumber), sprites));
    map->statics.push_back(new MapObject(0, 0, 450, 200, false));
    map->statics.push_back(new Controlpoint(800, 800, 1, 50, true));
    game_status->map = map;


    Camera camera = Camera(0, 0);
    //define a pointer to the player
    std::list<Player*>::iterator pit = map->fetch_pit(client_number);

#ifdef DEBUG_MODE    
    unsigned long frameNumber = 0;
#endif
    bool mouse_west = false;
    bool mouse_east = false;
    bool mouse_north = false;
    bool mouse_south = false;
    Minimap* minimap = new Minimap("resources/map.bmp", windowWidth, windowHeight);
    int frameCounter = 0;
    int updateInterval = 10;
    while (game_status->game_state == 2) {
        if(frameCounter%updateInterval == 0){
            map->transmit_changes();
        }
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (key[ALLEGRO_KEY_ESCAPE]) {
                    game_status->game_state = 1;
                }

                if (key[ALLEGRO_KEY_A]) {
                    camera.move_x(-20);
                }

                if (key[ALLEGRO_KEY_D]) {
                    camera.move_x(20);
                }

                if (key[ALLEGRO_KEY_W]) {
                    camera.move_y(-20);
                }

                if (key[ALLEGRO_KEY_S]) {
                    camera.move_y(20);
                }
                
                if (key[ALLEGRO_KEY_U]) {

//#ifdef DEBUG_MODE
       //             std::cout << "Spell at address " << &spell << std::endl;
//#endif
//                   map->spells.push_back(spell);
//#ifdef DEBUG_MODE
 //                   std::cout << "Done spell at " << &(map->spells) << std::endl;
//#endif
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                {
                    const int amountOfMovement = 20;
                    if (mouse_west) {
                        camera.move_x(-amountOfMovement);
                    }
                    if (mouse_east) {
                        camera.move_x(amountOfMovement);
                    }
                    if (mouse_north) {
                        camera.move_y(-amountOfMovement);
                    }
                    if (mouse_south) {
                        camera.move_y(amountOfMovement);
                    }
                }

                map->move_list(map->players);
                map->move_list(map->spells);
#ifdef DEBUG_MODE
                std::cout << "Players moved on frame " << frameNumber << std::endl;
#endif
                map->check_collisions();
#ifdef DEBUG_MODE
                std::cout << "Collisions checked, redrawing frame " << frameNumber << std::endl;                
                frameNumber++;
#endif
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                {
                    float proportionOfScroll = 0.1;
                    mouse_west = event.mouse.x < proportionOfScroll*windowWidth;
                    mouse_east = event.mouse.x > (1-proportionOfScroll)*windowWidth;
                    mouse_north = event.mouse.y < proportionOfScroll*windowHeight;
                    mouse_south = event.mouse.y > (1-proportionOfScroll)*windowHeight;
                    break;
                }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button == 2) {
                    (*pit)->set_dest(event.mouse.x / sx + camera.get_x(), event.mouse.y / sy + camera.get_y());
                }
                if (event.mouse.button == 1) {
                    double dy = (event.mouse.y / sy + camera.get_y()) - ((*pit)->get_y() + (*pit)->get_height()/2);
                    double dx = (event.mouse.x / sx + camera.get_x()) - ((*pit)->get_x() + (*pit)->get_width()/2);
                    double norm = sqrt(dy*dy + dx*dx);
                    dy = dy/norm;
                    dx = dx/norm;
                    map -> spells.push_back(new Rock(0, (*pit)->get_x() + (*pit)->get_width()/2 + 2*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 2*dy*(*pit)->get_height(),dx,dy));
                // defne the direction vector when right-click//
                break;
                }

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_status->game_state = 0;
                break;

	        default:
		        break;
        }

        if(game_status->game_state == 0)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));

            map->draw_map(camera.get_x(), camera.get_y());

            map->draw_list(map->players, camera.get_x(), camera.get_y());

            minimap->draw(map->players);
            map->draw_list(map->spells, camera.get_x(), camera.get_y());

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }

        frameCounter++;
    }
    //delete what you loaded
    delete map;
    delete minimap;
}

void must_init(bool test, const char *description) {
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void change_state(short & state, short new_state) {
    state = new_state;
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
    ALLEGRO_DISPLAY* disp = al_create_display(1920, 1080); //Change this resolution to change window size
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

    int playerNumber = -1;

    Gamestatus game_status(/*game_state*/ 1, /*map pointer*/0, &playerNumber);

    /*
    Game state states:
    0 => End game
    1 => main menu
    2 => game loop
    3 => settings?
    4 => ??? Profit??????
    */
    bool redraw = true;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    

    bool isServer = std::stoi(argv[1]);
    boost::asio::io_service io_service;
    Interface interface;
    if(isServer){
        playerNumber = 0;
        interface = Server(io_service, 13, &game_status);
    } else {
        interface = Client(io_service, "localhost", "13", &game_status);

        // request connection and player number;
        // 9 => Dummy player number
        // 3 => game info
        // 0 => register and request player number
        interface.send_message(std::string("930"));
    }
    
    // block the game until the player is registered
    while(playerNumber < 0)
        ;

    
    al_start_timer(timer);
    while (game_status.game_state != 0) {
        if (game_status.game_state == 1) {
            main_menu_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, sx, sy);
        }
        if (game_status.game_state == 2) {
            game_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, windowWidth, windowHeight, scaleX,
                     scaleY, scaleW, scaleH, sx, sy, interface);
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}

// define the vector when right-clicking
int direction(int click_x, int click_y, int loc_x, int loc_y){
    return (click_y - loc_y)/(click_x - loc_x);
}