//#define DEBUG_MODE
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <algorithm>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../headers/Map.hpp"
#include "../headers/Camera.hpp"
#include "../headers/MapObject.hpp"
#include "../headers/Player.hpp"
#include "../headers/Button.hpp"
#include "../headers/HUDobject.hpp"
#include "../headers/Minimap.hpp"
#include "../headers/ElementPicker.hpp"
#include "../headers/Spells.hpp"
#include "../headers/Projectile.hpp"
#include "../headers/Rock.hpp"
#include "../headers/Ice.hpp"
#include "../headers/HealP.hpp"
#include "../headers/FirePellet.hpp"
#include "../headers/Zone.hpp"
#include "../headers/HealZone.hpp"
#include "../headers/HealB.hpp"
#include "../headers/DealingB.hpp"
#include "../headers/WaterB.hpp"
#include "../headers/Beam.hpp"
#include "../headers/DZone.hpp"
#include "../headers/FogZone.hpp"
#include "../headers/FreezeZone.hpp"
#include "../headers/HealFireZone.hpp"
#include "../headers/Spray.hpp"
#include "../headers/WaterSpray.hpp"
#include "../headers/Shield.hpp"
#include "../headers/MainShield.hpp"
#include "../headers/WaterShield.hpp"
#include "../headers/FireShield.hpp"
#include "../headers/RockShield.hpp"
#include <cmath>
#include "../headers/Controlpoint.hpp"
#include "../headers/FireSpray.hpp"
#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Interface.hpp"
#include "../headers/Gamestatus.hpp"



#define KEY_SEEN     1
#define KEY_RELEASED 2

void must_init(bool, const char);
void change_state(short &, short new_state);
void Settings_write(int res_1, int res_2, int vsync);
int* Settings_read();
void change_resolution(int res_1, int res_2);
void change_vsync(int vsync);
void main_menu_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, const float&, const float&);

void game_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, Interface &interface, bool &isServer);

void settings_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, Interface &interface, bool &isServer);

void ip_input_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, Interface &interface, bool &isServer);

void np_input_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, Interface &interface, bool &isServer);

void red_game_end_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, const float&, const float&);

void blue_game_end_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, const float&, const float&);

void main_menu_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy) {
    //Load what you need to before the loop:
    ALLEGRO_BITMAP *menu_background = al_load_bitmap("resources/background.bmp");
    void (*changeptr)(short &, short new_state);
    changeptr = change_state;
    Button<short &, short>* create_game = new Button<short &, short>(840, 500, "resources/start.bmp", changeptr);
    Button<short &, short>* join_game = new Button<short &, short>(840, 600, "resources/join_game.bmp", changeptr);
    Button<short &, short>* settings = new Button<short &, short>(840, 800, "resources/settings.bmp", changeptr);
    Button<short &, short>* end_game = new Button<short &, short>(840, 700, "resources/exit.bmp", changeptr);

    while(game_status->game_state == 1) {
    al_wait_for_event(queue, &event);
    switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                    game_status->game_state = 0;
                }
                if (key[ALLEGRO_KEY_ENTER]) {
                    game_status->game_state = 2;
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                create_game->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 9);
                join_game->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 8);
                settings->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 3);
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
                break;ALLEGRO_SAMPLE* music11;

            default:
                break;
        }
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_scaled_bitmap(menu_background, 0, 0, al_get_bitmap_width(menu_background), al_get_bitmap_height(menu_background), 0, 0, 1920, 1080, 0);
            create_game->draw();
            join_game->draw();
            settings->draw();
            end_game->draw();
            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }
    //delete what you loaded
    delete create_game;
    delete join_game;
    delete settings;
    delete end_game;
}

void red_game_end_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, short client_number) {
    ALLEGRO_BITMAP *endgame_background = al_load_bitmap("resources/red_team_won.bmp");
    void (*changeptr)(short &, short new_state);
    changeptr = change_state;
    Button<short &, short>* main_menu = new Button<short &, short>(840, 900, "resources/main_menu.bmp", changeptr);

    ALLEGRO_SAMPLE* victory01 = al_load_sample("resources/victory01.wav");
    ALLEGRO_SAMPLE* victory02 = al_load_sample("resources/victory02.wav"); //Play the background music

    ALLEGRO_SAMPLE_INSTANCE* victory01_instance = al_create_sample_instance(victory01);

    ALLEGRO_SAMPLE* defeat01 = al_load_sample("resources/victory01.wav");
    ALLEGRO_SAMPLE* defeat02 = al_load_sample("resources/victory02.wav"); //Play the background music

    ALLEGRO_SAMPLE_INSTANCE* defeat01_instance = al_create_sample_instance(defeat01);


    if (client_number == 1) {
        al_attach_sample_instance_to_mixer(victory01_instance, al_get_default_mixer());
        al_set_sample_instance_playing(victory01_instance, true);
    }

    else {
        al_attach_sample_instance_to_mixer(defeat01_instance, al_get_default_mixer());
        al_set_sample_instance_playing(defeat01_instance, true);
    }

    while(game_status->game_state == 6) {
    al_wait_for_event(queue, &event);
    switch(event.type)
        {   
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                    game_status->game_state = 0;
                }
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                
                if(!al_get_sample_instance_playing(victory01_instance) && client_number == 1) {
                    al_play_sample(victory02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
                }

                if(!al_get_sample_instance_playing(defeat01_instance) && client_number != 1) {
                    al_play_sample(defeat02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
                }

                redraw = true;
                break;
            
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
            
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                main_menu->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 1);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_status->game_state = 0;
                break;

            default:
                break;

        }
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(255, 0, 0));

            al_draw_scaled_bitmap(endgame_background, 0, 0, al_get_bitmap_width(endgame_background), al_get_bitmap_height(endgame_background), 0, 0, 1920, 1080, 0);
            main_menu->draw();
            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }
    //delete what you loaded
    delete main_menu;
    al_destroy_bitmap(endgame_background);
}

void blue_game_end_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, int client_number) {
    ALLEGRO_BITMAP *endgame_background = al_load_bitmap("resources/blue_team_won.bmp");
    // map->get_winner() == 1
    ALLEGRO_SAMPLE* victory01 = al_load_sample("resources/victory01.wav");
    ALLEGRO_SAMPLE* victory02 = al_load_sample("resources/victory02.wav"); //Play the background music

    ALLEGRO_SAMPLE_INSTANCE* victory01_instance = al_create_sample_instance(victory01);

    ALLEGRO_SAMPLE* defeat01 = al_load_sample("resources/victory01.wav");
    ALLEGRO_SAMPLE* defeat02 = al_load_sample("resources/victory02.wav"); //Play the background music

    ALLEGRO_SAMPLE_INSTANCE* defeat01_instance = al_create_sample_instance(defeat01);


    if (client_number == 1) {
        al_attach_sample_instance_to_mixer(defeat01_instance, al_get_default_mixer());
        al_set_sample_instance_playing(defeat01_instance, true);
    }

    else {
        al_attach_sample_instance_to_mixer(victory01_instance, al_get_default_mixer());
        al_set_sample_instance_playing(victory01_instance, true);
    }
    void (*changeptr)(short &, short new_state);
    changeptr = change_state;
    Button<short &, short>* main_menu = new Button<short &, short>(840, 900, "resources/main_menu.bmp", changeptr);

    while(game_status->game_state == 7) {
    al_wait_for_event(queue, &event);
    switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                    game_status->game_state = 0;
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                if(!al_get_sample_instance_playing(defeat01_instance) && client_number == 1) {
                    al_play_sample(defeat02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
                }

                if(!al_get_sample_instance_playing(victory01_instance) && client_number != 1) {
                    al_play_sample(victory02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
                }

                redraw = true;
                break;
            
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
            
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                main_menu->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 1);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_status->game_state = 0;
                break;

            default:
                break;

        }
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(255, 0, 0));

            al_draw_scaled_bitmap(endgame_background, 0, 0, al_get_bitmap_width(endgame_background), al_get_bitmap_height(endgame_background), 0, 0, 1920, 1080, 0);
            main_menu->draw();
            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }
    //delete what you loaded
    delete main_menu;
    al_destroy_bitmap(endgame_background);
    al_destroy_sample(victory01);
    al_destroy_sample(victory02);
}

void game_loop (Gamestatus* game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer, 
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight,
                    const float &windowWidth, const float &windowHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, Interface* &interface, bool &isServer, short client_number) {
    //Load what you need to load
    
    Map* map=(interface->map);
    Minimap* minimap = new Minimap("resources/map.bmp", windowWidth, windowHeight);
    //map->decode_players("0.14868.815.713");
    map->set_spawnpoints(500, 1450, 1700, 1100, 3050, 700);
    map->players.push_back(new Player(400, 1050, 1,1));
    map->players.push_back(new Player(2950, 900, 2,2));
    map->cp.push_back(new Controlpoint(500, 1450, 1, 128, 0));
    map->cp.push_back(new Controlpoint(1700, 1100, 1, 128, 0));
    map->cp.push_back(new Controlpoint(3050, 700, 1, 128, 0));
    map->statics.push_back(new MapObject(0, 0, 250, 2160, false));
    map->statics.push_back(new MapObject(0, 0, 3840, 200, false));
    map->statics.push_back(new MapObject(0, 1910, 3840, 250, false));
    map->statics.push_back(new MapObject(3590, 0, 250, 2160, false));
    map->statics.push_back(new MapObject(0, 0, 800, 350, false));
    map->statics.push_back(new MapObject(0, 1710, 800, 450, false));
    map->statics.push_back(new MapObject(3040, 0, 800, 350, false));
    map->statics.push_back(new MapObject(3240, 1550, 600, 600, false));
    map->statics.push_back(new MapObject(2002, 1020, 840, 250, false));
    map->statics.push_back(new MapObject(2102, 1270, 840, 200, false));
    map->statics.push_back(new MapObject(2202, 1470, 840, 150, false));
    map->statics.push_back(new MapObject(200, 200, 120, 120, false));
    game_status->map = map;
    Camera camera = Camera(0, 0);
    bool left_mouse_down = false;
    int mouse_x;
    int mouse_y;
    float dxp;
    float dyp;
    int counter=0;
    // Animation indexes of the list: 0-2: Idle / 3-6: walking right animation / 7-10: walking left animation / 11: cast frame / 13 damaged ?/ 14-??: death animation
    //define a pointer to the player
    std::list<Player*>::iterator pit = map->fetch_pit(client_number);
    int e1 = 11; // default spell is rock
    int e2 = 11; // default spell is rock
    ElementPicker* e1p = new ElementPicker(screenWidth * 0.9, screenHeight*0.76, screenWidth * 0.06, screenWidth * 0.06, &e1);
    ElementPicker* e2p = new ElementPicker(screenWidth * 0.85, screenHeight*0.85, screenWidth * 0.06, screenWidth * 0.06, &e2);
    unsigned int cooldowns[122];
    for (int i = 0; i < 122; i++) {
        cooldowns[i] = 0;
    }
    bool spell_created;


#ifdef DEBUG_MODE
    unsigned long frameNumber = 0;
#endif
    bool mouse_west = false;
    bool mouse_east = false;
    bool mouse_north = false;
    bool mouse_south = false;
    
    while (game_status->game_state==2) {
        if (map->game_ended()){
            if (map->get_winner() == 1){
                game_status->game_state=6;
            }
            else{
                game_status->game_state=7;
            }
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
                    // camera.cameraUpdate(cameraPosition, x, y, 32, 32);
                    // al_identity_transform(camera);
                    // al_translate_transform(camera, -cameraPosition[0], -cameraPosition[1]);
                    // al_use_transform(camera);
                }

                for (int i = 0; i < 122; i++) {
                    if (cooldowns[i] != 0) {
                        cooldowns[i]--;
                    }
                }
                map->check_collisions();
                map->move_list(map->players);
                map->move_list(map->spells);
#ifdef DEBUG_MODE
                std::cout << "Players moved on frame " << frameNumber << std::endl;
#endif
#ifdef DEBUG_MODE
                std::cout << "Collisions checked, redrawing frame " << frameNumber << std::endl;
                frameNumber++;
#endif
                map->check_dead();
                map->garbage_collect();
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                {
                    mouse_x = event.mouse.x;
                    mouse_y = event.mouse.y;
                    float proportionOfScroll = 0.1;
                    mouse_west = event.mouse.x < proportionOfScroll*windowWidth;
                    mouse_east = event.mouse.x > (1-proportionOfScroll)*windowWidth;
                    mouse_north = event.mouse.y < proportionOfScroll*windowHeight;
                    mouse_south = event.mouse.y > (1-proportionOfScroll)*windowHeight;
                    dxp = (event.mouse.x / sx + camera.get_x()) - ((*pit)->get_x() + ((*pit)->get_width()/2));
                    dyp = (event.mouse.y / sy + camera.get_y()) - ((*pit)->get_y() + ((*pit)->get_height()/2));
                    float n2 =  sqrt(dyp*dyp + dxp*dxp);
                    dxp = dxp/n2;
                    dyp = dyp/n2;

                    break;
                }

            case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
                mouse_east = false;
                mouse_west = false;
                mouse_north = false;
                mouse_south = false;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button == 2) {
                    (*pit)->set_dest(event.mouse.x / sx + camera.get_x(), event.mouse.y / sy + camera.get_y());
                }
                if (event.mouse.button == 1) {
                    spell_created=true;
                    double dy = (event.mouse.y / sy + camera.get_y()) - ((*pit)->get_y() + ((*pit)->get_height()/2));
                    double dx = (event.mouse.x / sx + camera.get_x()) - ((*pit)->get_x() + ((*pit)->get_width()/2));
                    double norm = sqrt(dy*dy + dx*dx);
                    double dx1=dx;
                    double dy1=dy;
                    //why do we need dx1 and dy1 here
                    dy = dy/norm;
                    dx = dx/norm;
                    // std::cout << e1*e2;
                    switch(e1*e2) {
                        case 121: // 11*11 L+L Rock+Rock
                            if (cooldowns[121] == 0) {
                                map -> spells.push_back(new Rock((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                                cooldowns[121] = 15;
                            }
                            break;
                        case 49: // 7*7 K+K Ice+Ice
                            if (cooldowns[49] == 0) {
                                map -> spells.push_back(new Ice((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                                cooldowns[49] = 10;
                            }
                            break;
                        case 7: // 7*1 K+U Ice+Life
                            if (cooldowns[7] == 0) {
                                map -> spells.push_back(new HealP((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                                cooldowns[7] = 15;
                            }
                            break;
                        case 33: // 11*3 L+O Rock+Fire
                            if (cooldowns[33] == 0) {
                                map -> spells.push_back(new FireP((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                                cooldowns[33] = 20;
                            }
                            break;
                        case 2: // 2*1 I+U Shield+Life
                            if (cooldowns[2] == 0) {
                                if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                    map -> spells.push_back(new HealZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                                }
                                else {
                                    map -> spells.push_back(new HealZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                                }
                                if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                    map -> spells.push_back(new HealZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                                }
                                else {
                                    map -> spells.push_back(new HealZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                                }
                                cooldowns[2] = 45;
                            }
                            break;
                        case 3: // 3*1 O+U Fire+Life
                            if (cooldowns[3] == 0) {
                                if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                map -> spells.push_back(new HealFireZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                                }
                                else {
                                map -> spells.push_back(new HealFireZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                                }
                                cooldowns[3] = 45;
                            }
                            break;

                        case 5: // 5*1 J+U Water+Life
                            if(cooldowns[5] == 0) {
                                if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                map -> spells.push_back(new DamageZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                                }
                                else {
                                map -> spells.push_back(new DamageZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                                }
                                cooldowns[5] = 5;
                            }
                            break;
                        case 15: // 3*5 O+J Fire+Water
                            if (cooldowns[15] == 0) {
                                if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                map -> spells.push_back(new FogZ((*pit)->get_x() - (*pit)->get_width()/2+4*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+4*dy*(*pit)->get_height()));
                                }
                                else {
                                map -> spells.push_back(new FogZ(event.mouse.x / sx + camera.get_x() - 3*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 3*(*pit)->get_height()));
                                }
                                cooldowns[15] = 45;
                            }

                            break;
                        case 77: // 7*11 K+L Ice+Rock
                            if (cooldowns[77] == 0) {
                                if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                map -> spells.push_back(new FreezeZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                                }
                                else {
                                map -> spells.push_back(new FreezeZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                                }
                                cooldowns[77] = 45;
                            }
                            break;
                        case 1: // 1*1 U+U Life + Life = Healing beam
                            if (cooldowns[1] == 0) {
                                map -> spells.push_back(new HealB(pit, &dxp, &dyp, &left_mouse_down, map));
                                cooldowns[1] = 5;
                            }
                            break;
                        case 21: // 3*7 Ice + Fire = Dealing Beam
                            map -> spells.push_back(new DealingB(pit, &dxp, &dyp, &left_mouse_down, map));
                            break;
                        case 55: // 5*11 Rock + Water = Water Beam
                            map -> spells.push_back(new WaterB(pit, &dxp, &dyp, &left_mouse_down, map));
                            break;
                        case 25: //5*5 Water + Water = Water Spray
                            map -> spells.push_back(new WaterSpray(pit, &dxp, &dyp, &left_mouse_down, map));
                            break;
                        case 4: // 2*2 I+I Shield + Shield = Main shield
                            if (cooldowns[4] == 0) {
                                int pmx = (*pit)->get_x() + (*pit)->get_width()/2;
                                int pmy = (*pit)->get_y() + (*pit)->get_height()/2;
                                double rx = dy;
                                double ry = -1*dx;
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width(),pmy + 1.5*dy*(*pit)->get_height(), dx, dy,true));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() + 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 5*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() - 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 5*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() + 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 4*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() - 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 4*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() + 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 3*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() - 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 3*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() + 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 2*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() - 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 2*ry*12, dx, dy,false));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() + 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 1*ry*12, dx, dy,true));
                                map->statics.push_back(new MainShield(pmx + 1.5*dx*(*pit)->get_width() - 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 1*ry*12, dx, dy,true));
                                cooldowns[4] = 40;
                            }
                            break;

                        case 10: // 2*5 I+J Shield + Water = Water shield
                            if (cooldowns[4] == 0) {
                                int pmx = (*pit)->get_x() + (*pit)->get_width()/2;
                                int pmy = (*pit)->get_y() + (*pit)->get_height()/2;
                                double rx = dy;
                                double ry = -1*dx;
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width(),pmy + 1.5*dy*(*pit)->get_height(), dx, dy,true));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() + 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 5*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() - 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 5*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() + 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 4*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() - 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 4*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() + 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 3*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() - 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 3*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() + 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 2*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() - 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 2*ry*12, dx, dy,false));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() + 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 1*ry*12, dx, dy,true));
                                map->statics.push_back(new WaterShield(pmx + 1.5*dx*(*pit)->get_width() - 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 1*ry*12, dx, dy,true));
                                cooldowns[4] = 40;
                            }
                            break;

                        case 6: // 2*3 I+O Shield + fire = fire shield
                            if (cooldowns[4] == 0) {
                                int pmx = (*pit)->get_x() + (*pit)->get_width()/2;
                                int pmy = (*pit)->get_y() + (*pit)->get_height()/2;
                                double rx = dy;
                                double ry = -1*dx;
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width(),pmy + 1.5*dy*(*pit)->get_height(), dx, dy,true));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() + 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 5*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() - 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 5*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() + 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 4*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() - 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 4*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() + 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 3*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() - 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 3*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() + 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 2*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() - 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 2*ry*12, dx, dy,false));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() + 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 1*ry*12, dx, dy,true));
                                map->statics.push_back(new FireShield(pmx + 1.5*dx*(*pit)->get_width() - 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 1*ry*12, dx, dy,true));
                                cooldowns[4] = 40;
                            }
                            break;

                        case 22: // 2*11 I+L Shield + rock = rock shield
                            if (cooldowns[4] == 0) {
                                int pmx = (*pit)->get_x() + (*pit)->get_width()/2;
                                int pmy = (*pit)->get_y() + (*pit)->get_height()/2;
                                double rx = dy;
                                double ry = -1*dx;
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width(),pmy + 1.5*dy*(*pit)->get_height(), dx, dy,true));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() + 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 5*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() - 5*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 5*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() + 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 4*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() - 4*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 4*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() + 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 3*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() - 3*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 3*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() + 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 2*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() - 2*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 2*ry*12, dx, dy,false));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() + 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() + 1*ry*12, dx, dy,true));
                                map->statics.push_back(new RockShield(pmx + 1.5*dx*(*pit)->get_width() - 1*rx*12, pmy + 1.5*dy*(*pit)->get_height() - 1*ry*12, dx, dy,true));
                                cooldowns[4] = 40;
                            }
                            break;

                        case 9: // 3*3 O + O Fire + Fire = Fire Spray
                            map -> spells.push_back(new FireSpray(pit, &dxp, &dyp, &left_mouse_down, map));
                            break;
                        case 11: // 11*1 U+L life+rock Autoheal
                            (*pit)->hit(-10);
                            break;

                        default:

                       // } else if (std::count(elementlist.begin(),elementlist.end(),1)==1 && std::count(elementlist.begin(),elementlist.end(),2)==1) {
                       //     map -> spells.push_back(new HealZ(event.mouse.x - (*pit)->get_width()/2,event.mouse.y - (*pit)->get_height()/2));
                     //   } else if (std::count(elementlist.begin(),elementlist.end(),1)==2) {
                   //         map -> spells.push_back(new HealB((*pit)->get_x() + (*pit)->get_width()/2 + 2*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 2*dy*(*pit)->get_height(),dx,dy));
                            std::cout << "No spells associated to this combo of two buttons" << std::endl;
                            break;
                    }
                    left_mouse_down = true;
                    // if (elementlist.size() == 2) {
                    //     if (std::count(elementlist.begin(),elementlist.end(),6)==2) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),5)==2) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),5)==1 && std::count(elementlist.begin(),elementlist.end(),1)==1) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),6)==1 ALLEGRO_SAMPLE* music11;&& std::count(elementlist.begin(),elementlist.end(),3)==1) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),1)==1 && std::count(elementlist.begin(),elementlist.end(),2)==1) {
                    //     } else {
                    //     }
                    // } else {
                    // }
                // define the direction vector when right-click//
                }
            break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (event.mouse.button == 1) {
                    left_mouse_down = false;
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_U) {//life
                    e2=e1;
                    e1=1;

                    //elementlist.push_back(1);
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_I) {//shield
                    e2=e1;
                    e1=2;
                    //elementlist.push_back(2);
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_O) {//fire
                    e2=e1;
                    e1=3;
                    //elementlist.push_back(3);
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_J) {//water
                    e2=e1;
                    e1=5;
                    //elementlist.push_back(4);c++ initialze a int
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_K) {//ice
                    e2=e1;
                    e1=7;
                    //elementlist.push_back(5);
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_L) {//rock
                    e2=e1;
                    e1=11;
                    //elementlist.push_back(6);
                }
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

            map->draw_list(map->cp, camera.get_x(), camera.get_y());

            map->draw_list(map->statics, camera.get_x(), camera.get_y());


            map->draw_list(map->players, camera.get_x(), camera.get_y());

            map->draw_list(map->spells, camera.get_x(), camera.get_y());

            e1p->draw();
            e2p->draw();

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            minimap->draw(map->players, map->cp);
            al_flip_display();

            redraw = false;
            if(isServer){
                for(std::list<Spell*>::iterator i = map->spells.begin(); i != map->spells.end(); i++){
                    (*i)->counter++;
                    if((*i)->isBorS && (*i)->counter>20){
                        (*i)->counter=0;
                        for(int j=1; j<5; j++){
                            (*i)->transmitted[j]=false;
                        }
                    }
                    if(!(*i)->isBorS && (*i)->counter>30){
                        (*i)->counter=0;
                        for(int j=1; j<5; j++){
                            (*i)->transmitted[j]=false;
                        }
                    }
                }
            }
        }

        if(!isServer){
                counter++;
                counter=counter%10;
                if (counter==1){
                    (*interface).send_string("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaathisisplayer:"+(*pit)->encode_player());
                }
                if (spell_created){
                    spell_created=false;
                    for(std::list<Spell*>::iterator i = map->spells.begin(); i != map->spells.end(); i++){
                        if(!(*i)->transmitted[1]){
                            (*i)->transmitted[1]=true;
                            (*i)->transmitted[client_number]=true;
                            (*interface).send_string((*i)->encode_spell());
                        }
                    }
                    for(std::list<MapObject*>::iterator i = map->statics.begin(); i != map->statics.end(); i++){
                        if(!(*i)->transmitted[1]){
                            std::cout<<"Found shield"<<std::endl;
                            (*i)->transmitted[1]=true;
                            (*i)->transmitted[client_number]=true;
                            (*interface).send_string((*i)->encode_spell());
                        }
                    }
                }
                // for(std::list<Spell*>::iterator i = map->spells.begin(); i != map->spells.end(); i++){
                //     if((*i)->isBorS){
                //         ((*i)->counter)++;
                //         if(((*i)->counter)>20){
                //             (*i)->set_mouse_down(map->iamnot);
                //         }
                //     }
                // }
            }
        }
    //delete what you loaded
    delete map;
    delete minimap;
}

void server_loop(Gamestatus *game_status, Interface* &interface, bool &isServer){
    delete interface;
    isServer = true;
    boost::asio::io_service io_service;
    interface = new Server(io_service, 13, &*game_status, 2);
    while(!interface->ready){
        std::cout<<"Not yet"<<std::endl;
    }
    std::cout<<"..."<<std::endl;
    game_status->game_state=2;
}

void client_loop(Gamestatus *game_status, Interface* &interface, bool &isServer, short &client_number, std::string &ip){
    delete interface;
    isServer = false;
    boost::asio::io_service io_service;
    interface = new Client(io_service, ip, "13", &*game_status);
    while(!interface->connected && !interface->ready){
        int counter0=al_get_time();
        int counter=0;
        interface->send_string("aaaaaaaready");
        std::cout<<"Sent !"<<std::endl;
        while(!interface->connected && counter<counter0+2){
            counter=al_get_time();
        }
    }
    while(!interface->ready){
        int counter0=al_get_time();
        int counter=0;
        interface->send_string("aaaaaaaaastillthere");
        std::cout<<"Sent !"<<std::endl;
        while(!interface->ready && counter<counter0+2){
            counter=al_get_time();
        }
    }
    client_number=interface->get_client();
    game_status->game_state=2;
    
    /*for(int i=0; i<10000; i++){
        if(interface->ready){
            game_status->game_state=2;
            break;
        }
    }
    if(!interface->ready){
        game_status->game_state=1;
    }*/
}


void change_resolution(int res_1, int res_2) {
    int* values = Settings_read();
    int vsync = values[2];
    Settings_write(res_1, res_2, vsync);
    std::cout << res_1 << " " << res_2 << std::endl;
}

void change_vsync(int vsync) {
    int* values = Settings_read();
    int res_1 = values[0];
    int res_2 = values[1];
    Settings_write(res_1, res_2, vsync);
    std::cout << vsync << std::endl;
}

void Settings_write(int res_1, int res_2, int vsync){
    using namespace std;
    ofstream outf("Settings.txt");
    if (!outf){
        cerr << "Unable to open Settings.txt" <<endl;
        exit(1);
    }
    outf << res_1 << endl;
    outf << res_2 << endl;
    outf << vsync << endl;
    // outf << "Resolution" << endl;
    // outf << "Buffer" << endl;
    // outf << "VSYNC" << endl;
}

int* Settings_read() {
	using namespace std;
	ifstream myfile("Settings.txt"); 
    std::vector<std::string> vt;
	if (myfile.is_open()) 
	{
        std::string line;
        
        vt.reserve(3);
		while (getline(myfile, line)) {
            vt.push_back(std::move(line));
            
	    }
        myfile.close(); 
         std::cout << vt[0] <<std::endl;
         std::cout << vt[1] <<std::endl;
         std::cout << vt[2] <<std::endl;
    } else { 
        cerr << "Unable to open Settings.txt" <<endl;
        int* res = new int[3];
        res[0] = 1920; 
        res[1] = 1080;
        res[2] = 2;
        return res;
    } 
	// for(l_2=0;l_2<=l;l_2++){ 
	// 	cout<<array[l_2]<<endl;    
    // }
    
    
    int* res = new int[3];
    try {
        res[0] = stoi(vt[0]); 
        res[1] = stoi(vt[1]);
        res[2] = stoi(vt[2]);
    }
    catch(...) {
        res[0] = 1920; 
        res[1] = 1080;
        res[2] = 2;
    }
    return res;
}

void settings_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy) {
    ALLEGRO_BITMAP *settings_background = al_load_bitmap("resources/background.bmp");
    ALLEGRO_FONT *main_menu_font = al_load_font("resources/DejaVuSans.ttf",75,0);
    void (*changeptr)(short &, short new_state);
    changeptr = change_state;
    Button<short &, short>* return_main_menu= new Button<short &, short>(130, 140, "resources/main_menu.bmp", changeptr);
    Button<short &, short>* quit= new Button<short &, short>(1550, 950, "resources/exit.bmp", changeptr);
    void (*res_ptr)(int, int);
    res_ptr = change_resolution;
    Button<int, int>* resolution_1= new Button<int, int>(530, 410, "resources/res_1.bmp", res_ptr);
    Button<int, int>* resolution_2= new Button<int, int>(830, 410, "resources/res_2.bmp", res_ptr);
    Button<int, int>* resolution_3= new Button<int, int>(1130, 410, "resources/res_3.bmp", res_ptr);
    Button<int, int>* resolution_4= new Button<int, int>(1430, 410, "resources/res_4.bmp", res_ptr);
    void (*vsync_ptr)(int);
    vsync_ptr = change_vsync;
    Button<int>* vsync_on= new Button<int>(480, 610, "resources/ON_1.bmp", vsync_ptr);
    Button<int>* vsync_off= new Button<int>(830, 610, "resources/OFF_1.bmp", vsync_ptr);
    while(game_status->game_state == 3) {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                    game_status->game_state = 0;
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                return_main_menu->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 1);
                quit->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 0);
                resolution_1->mouse_input(event.mouse.x / sx, event.mouse.y / sy, 1024, 576);
                resolution_2->mouse_input(event.mouse.x / sx, event.mouse.y / sy, 1280, 720);
                resolution_3->mouse_input(event.mouse.x / sx, event.mouse.y / sy, 2560, 1440);
                resolution_4->mouse_input(event.mouse.x / sx, event.mouse.y / sy, 1664, 936);
                vsync_on->mouse_input(event.mouse.x / sx, event.mouse.y / sy, 1);
                vsync_off->mouse_input(event.mouse.x / sx, event.mouse.y / sy, 2);
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

            default:
                break;
        }
        if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            al_draw_scaled_bitmap(settings_background, 0, 0, al_get_bitmap_width(settings_background), al_get_bitmap_height(settings_background), 0, 0, 1920, 1080, 0);
            return_main_menu->draw();
            quit->draw();
            resolution_1->draw();
            resolution_2->draw();
            resolution_3->draw();
            resolution_4->draw();
            vsync_on->draw();
            vsync_off->draw();

            al_draw_text(main_menu_font,al_map_rgb(10,0,0),100,400,0,"Resolution");
            al_draw_text(main_menu_font,al_map_rgb(255,255,255),175,860,0,"Please restart game to apply changes.");
            al_draw_text(main_menu_font,al_map_rgb(10,0,0),100,600,0,"VSYNC");

            al_set_target_backbuffer(disp);
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();
            al_wait_for_event(queue, &event);

            redraw = false;   
                }
    }
  delete return_main_menu;   
  delete resolution_1;
  delete resolution_2; 
  delete resolution_3; 
  delete resolution_4;  
  delete quit;  
  delete vsync_on;
  delete vsync_off;  
}

void must_init(bool test, const char *description) {
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void change_state(short & state, short new_state) {
    state = new_state;
}

void np_input_loop(Gamestatus* game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer, 
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight,
                    const float &windowWidth, const float &windowHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, Interface* &interface, bool &isServer, short client_number, short &number_player) {

    ALLEGRO_FONT *DejaVuSans = al_load_font("resources/DejaVuSans.ttf",52,0);
    std::string input = "";

    while(game_status->game_state == 9) {
    al_wait_for_event(queue, &event);
    switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                if (event.keyboard.keycode == ALLEGRO_KEY_0) {
                    input.append("0");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_1) {
                    input.append("1");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_2) {
                    input.append("2");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_3) {
                    input.append("3");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_4) {
                    input.append("4");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_5) {
                    input.append("5");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_6) {
                    input.append("6");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_7) {
                    input.append("7");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_8) {
                    input.append("8");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_9) {
                    input.append("9");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && input.size() > 0) {
                    input.pop_back();
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    game_status->game_state=4;
                    number_player=std::stoi(input);
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    game_status->game_state = 1;
                }


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
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);
            int bw = al_get_bitmap_width(buffer);
            int bh = al_get_bitmap_height(buffer);

            al_clear_to_color(al_map_rgb(234, 231, 28));
            al_draw_text(DejaVuSans, al_map_rgb(0,0,0), bw / 2, bh / 2 - 2 * 52 - 16, 1, "Please enter the number of players to host:");
            al_draw_filled_rectangle(bw * 0.46, bh / 2 - 52, bw * 0.54, bh / 2 + 16, al_map_rgb(0,0,0));
            al_draw_filled_rectangle(bw * 0.46 + 5, bh / 2 - 47, bw * 0.54 - 5, bh / 2 + 11, al_map_rgb(234, 231, 28));
            al_draw_text(DejaVuSans, al_map_rgb(0,0,0), bw / 2, bh / 2 - 46, 1, input.c_str());
            al_draw_text(DejaVuSans, al_map_rgb(0,0,0), bw / 2, bh / 2 + 32, 1, "Press 'ENTER' to continue");

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }
    //delete what you loaded
    al_destroy_font(DejaVuSans);
}

void ip_input_loop(Gamestatus* game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer, 
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight,
                    const float &windowWidth, const float &windowHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, Interface* &interface, bool &isServer, short &client_number, std::string &ip) {

    ALLEGRO_FONT *DejaVuSans = al_load_font("resources/DejaVuSans.ttf",52,0);
    std::string input = "";
    bool can_enter = true;
    unsigned int counter = 0;

    while(game_status->game_state == 8) {
    al_wait_for_event(queue, &event);
    switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                if (event.keyboard.keycode == ALLEGRO_KEY_0) {
                    input.append("0");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_1) {
                    input.append("1");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_2) {
                    input.append("2");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_3) {
                    input.append("3");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_4) {
                    input.append("4");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_5) {
                    input.append("5");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_6) {
                    input.append("6");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_7) {
                    input.append("7");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_8) {
                    input.append("8");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_9) {
                    input.append("9");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_FULLSTOP) {
                    input.append(".");
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && input.size() > 0) {
                    input.pop_back();
                } if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    game_status->game_state=5;
                    ip=input;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    game_status->game_state = 1;
                }


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
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);
            int bw = al_get_bitmap_width(buffer);
            int bh = al_get_bitmap_height(buffer);

            al_clear_to_color(al_map_rgb(234, 231, 28));
            al_draw_text(DejaVuSans, al_map_rgb(0,0,0), bw / 2, bh / 2 - 2 * 52 - 16, 1, "Please enter server IP address:");
            al_draw_filled_rectangle(bw * 0.25, bh / 2 - 52, bw * 0.75, bh / 2 + 16, al_map_rgb(0,0,0));
            al_draw_filled_rectangle(bw * 0.25 + 5, bh / 2 - 47, bw * 0.75 - 5, bh / 2 + 11, al_map_rgb(234, 231, 28));
            al_draw_text(DejaVuSans, al_map_rgb(0,0,0), bw / 2, bh / 2 - 46, 1, input.c_str());
            al_draw_text(DejaVuSans, al_map_rgb(0,0,0), bw / 2, bh / 2 + 32, 1, "Press 'ENTER' to continue");

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
    }
    //delete what you loaded
    al_destroy_font(DejaVuSans);
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

    int* values = Settings_read();
    int res_1 = values[0];
    int res_2 = values[1];
    int vsync = values[2];

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_VSYNC, vsync, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    
    ALLEGRO_DISPLAY* disp = al_create_display(res_1, res_2); //Change this resolution to change window size
    //ALLEGRO_DISPLAY* disp = al_create_display(1280, 720); //Change this resolution to change window size

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
    float scaleY = (windowHeight - scaleH) / 2;ALLEGRO_SAMPLE* music11;

    must_init(al_init_primitives_addon(), "primitives");

    must_init(al_init_image_addon(), "Image addon");

    must_init(al_install_audio(), "Audio addon");
    must_init(al_init_acodec_addon(), "Audio codecs addon"); //Initialise the audio codecs. (for playing sound effects)
    must_init(al_reserve_samples(16), "reserve samples");
    must_init(al_init_font_addon(), "Font addon");
    must_init(al_init_ttf_addon(), "ttf addon");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());


    Gamestatus game_status(/*game_state*/ 1, /*map pointer*/0);
    Interface* interface=new Interface();
    bool isServer=true;
    short client_number=1;
    std::string ip;
    short player_number;
    /*
    Game state states:
    0 => Exit game
    1 => main menu
    2 => game loop
    3 => settings?
    4 => Create game
    5 => Join game
    6 => Game Ended Red
    7 => Game Ended Blue
    8 => Enter ip window


    */
    bool redraw = true;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);

    

    while (game_status.game_state != 0) {
        if (game_status.game_state == 1) {
            //main menu
            ALLEGRO_SAMPLE* music = al_load_sample("resources/menu.wav"); //Play the background music
            al_play_sample(music, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)

            main_menu_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, sx, sy);
            al_destroy_sample(music);
        }
        if (game_status.game_state == 2) {
            //game loop
            ALLEGRO_SAMPLE* music = al_load_sample("resources/main_game.wav"); //Play the background music
            al_play_sample(music, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)

            game_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, windowWidth, windowHeight, scaleX,
                    scaleY, scaleW, scaleH, sx, sy, interface, isServer, client_number);
            al_destroy_sample(music);
        }
        if (game_status.game_state == 3) {
            //settings
            ALLEGRO_SAMPLE* music = al_load_sample("resources/settings.wav"); //Play the background music
            al_play_sample(music, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)

            settings_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, sx, sy);
            al_destroy_sample(music);
        }
        if (game_status.game_state == 4){
            //create game ("server")
            ALLEGRO_SAMPLE* music = al_load_sample("resources/main_game.wav"); //Play the background music
            al_play_sample(music, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            server_loop(&game_status, interface, isServer);
            al_destroy_sample(music);
        }
        if (game_status.game_state == 5){
            //join game ("client")
            ALLEGRO_SAMPLE* music = al_load_sample("resources/main_game.wav"); //Play the background music
            al_play_sample(music, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); //(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            client_loop(&game_status, interface, isServer, client_number, ip);
            al_destroy_sample(music);
        }
        if (game_status.game_state == 6) {
            //game end
            // int i = 0;
            // ALLEGRO_SAMPLE* victory01 = al_load_sample("resources/victory01.wav"); //Play the background music
            // al_play_sample(victory01, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            // if (victory01) i += 1;
            // if (i == 1){
            //     al_destroy_sample(victory01);
            //     i += 1;
            // }
            // if (i == 2) {
            //     ALLEGRO_SAMPLE* victory02 = al_load_sample("resources/victory02.wav"); //Play the background music
            //     al_play_sample(victory02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            //     if (victory02) i += 1;
            //     if (i == 3){
            //     al_destroy_sample(victory01);
            //     i += 1;
            // }
            // }
            
            
            red_game_end_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, sx, sy, client_number);
        }
        if (game_status.game_state == 7) {
                        //game end
            // int i = 0;
            // ALLEGRO_SAMPLE* victory01 = al_load_sample("resources/victory01.wav"); //Play the background music
            // al_play_sample(victory01, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            // if (victory01) i += 1;
            // if (i == 1){
            //     al_destroy_sample(victory01);
            //     i += 1;
            // }
            // if (i == 2) {
            //     ALLEGRO_SAMPLE* victory02 = al_load_sample("resources/victory02.wav"); //Play the background music
            //     al_play_sample(victory02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            //     if (victory02) i += 1;
            //     if (i == 3){
            //     al_destroy_sample(victory01);
            //     i += 1;
            // }
            // }
            blue_game_end_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, sx, sy, client_number);
        }
        if (game_status.game_state == 8) {
            ip_input_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, windowWidth, windowHeight, scaleX,
                    scaleY, scaleW, scaleH, sx, sy, interface, isServer, client_number, ip);
        }
        if (game_status.game_state == 9) {
            np_input_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, windowWidth, windowHeight, scaleX,
                    scaleY, scaleW, scaleH, sx, sy, interface, isServer, client_number, player_number);
        }
    }

    delete interface;
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    

    return 0;
}

// define the vector when right-clicking
int direction(int click_x, int click_y, int loc_x, int loc_y){
    return (click_y - loc_y)/(click_x - loc_x);
}

void game_end_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy) {
        
        int i = 0;
        ALLEGRO_SAMPLE* victory01 = al_load_sample("resources/victory01.wav"); //Play the background music
        al_play_sample(victory01, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
        if (victory01) i += 1;
        if (i == 1){
            al_destroy_sample(victory01);
            i += 1;
        }
        if (i == 2) {
            ALLEGRO_SAMPLE* victory02 = al_load_sample("resources/victory02.wav"); //Play the background music
            al_play_sample(victory02, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//(SAMPLE NAME, gain(volumn), pan(balance), speed, play_mode, sample_id)
            if (victory02) i += 1;
            if (i == 3){
            al_destroy_sample(victory01);
            i += 1;
        }
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);



            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();

            redraw = false;
        }
}
