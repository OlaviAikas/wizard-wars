//#define DEBUG_MODE
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <algorithm>
#include <list>
#include <iostream>
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
#include "../headers/Beam.hpp"
#include "../headers/DZone.hpp"
#include "../headers/FogZone.hpp"
#include "../headers/FreezeZone.hpp"
#include "../headers/HealFireZone.hpp"
#include "../headers/Spray.hpp"
#include "../headers/WaterSpray.hpp"
#include "../headers/Shield.hpp"
#include "../headers/MainShield.hpp"
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
void main_menu_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, const float&, const float&);

void game_loop(Gamestatus *, bool &, ALLEGRO_EVENT_QUEUE* &, ALLEGRO_EVENT &, ALLEGRO_TIMER* &, unsigned char*, ALLEGRO_BITMAP* &,
                    ALLEGRO_DISPLAY* &, const float&, const float&, const float&, const float&, const float&, const float&, Interface &interface, bool &isServer);

void main_menu_loop(Gamestatus * game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer,
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy) {
    //Load what you need to before the loop:
    void (*changeptr)(short &, short new_state);
    changeptr = change_state;
    Button<short &, short>* create_game = new Button<short &, short>(840, 500, "resources/create_game.bmp", changeptr);
    Button<short &, short>* join_game = new Button<short &, short>(840, 600, "resources/join_game.bmp", changeptr);
    Button<short &, short>* end_game = new Button<short &, short>(840, 700, "resources/quit.bmp", changeptr);

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
                create_game->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 4);
                join_game->mouse_input(event.mouse.x / sx, event.mouse.y / sy, game_status->game_state, 5);
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

            default:
                break;
        }
            if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));
            create_game->draw();
            join_game->draw();
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
    delete end_game;
}



void game_loop (Gamestatus* game_status, bool &redraw, ALLEGRO_EVENT_QUEUE* &queue, ALLEGRO_EVENT &event, ALLEGRO_TIMER* &timer, 
                    unsigned char* key, ALLEGRO_BITMAP* &buffer, ALLEGRO_DISPLAY* &disp, const float &screenWidth, const float &screenHeight,
                    const float &windowWidth, const float &windowHeight, const float &scaleX,
                    const float &scaleY, const float &scaleW, const float &scaleH, const float &sx, const float &sy, Interface* &interface, bool &isServer, short client_number) {
    //Load what you need to load
    
    Map* map=(interface->map);
    Minimap* minimap = new Minimap("resources/map.bmp", windowWidth, windowHeight);
    map->set_spawnpoints(200, 300, 1500,  1800, 1500, 1500, 2000, 400);
    map->players.push_back(new Player(400, 400, 1,1));
    map->players.push_back(new Player(900, 900, 2,2));
    map->statics.push_back(new MapObject(0, 0, 450, 200, false));
    map->cp.push_back(new Controlpoint(1500, 1500, 1, 128, 0));
    map->cp.push_back(new Controlpoint(200, 300, 1, 128, 1));
    map->cp.push_back(new Controlpoint(2000, 400, 1, 128, 0));
    map->cp.push_back(new Controlpoint(3000, 1700, 1, 128, 0));
    map->statics.push_back(new MapObject(0, 0, 250, 2160, false));
    map->statics.push_back(new MapObject(0, 0, 3840, 200, false));
    map->statics.push_back(new MapObject(0, 1910, 3840, 250, false));
    map->statics.push_back(new MapObject(3590, 0, 250, 2160, false));
    map->statics.push_back(new MapObject(0, 0, 800, 350, false));
    map->statics.push_back(new MapObject(0, 1710, 800, 450, false));
    map->statics.push_back(new MapObject(3040, 0, 800, 350, false));
    map->statics.push_back(new MapObject(3240, 1550, 600, 600, false));
    map->statics.push_back(new MapObject(2002, 1020, 940, 590, false));
    map->modif_lives(50, 50);
    map->cp.push_back(new Controlpoint(3000, 1700, 1, 128, 2));
    game_status->map = map;
    Camera camera = Camera(0, 0);
    // Animation indexes of the list: 0-2: Idle / 3-6: walking right animation / 7-10: walking left animation / 11: cast frame / 13 damaged ?/ 14-??: death animation
    //define a pointer to the player
    std::list<Player*>::iterator pit = map->fetch_pit(client_number);
    int e1 = 0;
    int e2 = 0;
    ElementPicker* e1p = new ElementPicker(screenWidth * 0.9, screenHeight*0.76, screenWidth * 0.06, screenWidth * 0.06, &e1);
    ElementPicker* e2p = new ElementPicker(screenWidth * 0.85, screenHeight*0.85, screenWidth * 0.06, screenWidth * 0.06, &e2);


#ifdef DEBUG_MODE
    unsigned long frameNumber = 0;
#endif
    bool mouse_west = false;
    bool mouse_east = false;
    bool mouse_north = false;
    bool mouse_south = false;
    
    while (game_status->game_state==2) {
        if (map->game_ended()){
            game_status->game_state=0;
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
                map->check_dead();
                map->garbage_collect();
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
                    double dy = (event.mouse.y / sy + camera.get_y()) - ((*pit)->get_y() + (*pit)->get_height()/2);
                    double dx = (event.mouse.x / sx + camera.get_x()) - ((*pit)->get_x() + (*pit)->get_width()/2);
                    double norm = sqrt(dy*dy + dx*dx);
                    double dx1=dx;
                    double dy1=dy;
                    //why do we need dx1 and dy1 here
                    dy = dy/norm;
                    dx = dx/norm;
                    // std::cout << e1*e2;
                    switch(e1*e2) {
                        case 121: // 11*11 L+L Rock+Rock
                            map -> spells.push_back(new Rock((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                            break;
                        case 49: // 7*7 K+K Ice+Ice
                            map -> spells.push_back(new Ice((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                            break;
                        case 7: // 7*1 K+U Ice+Life
                            map -> spells.push_back(new HealP((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                            break;
                        case 33: // 11*3 L+O Rock+Fire
                            map -> spells.push_back(new FireP((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                            break;
                        case 2: // 2*1 I+U Shield+Life
                            if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                map -> spells.push_back(new HealZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                            }
                            else {
                                map -> spells.push_back(new HealZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                            }
                            break;
                        case 3: // 3*1 O+U Fire+Life
                            if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                            map -> spells.push_back(new HealFireZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                            }
                            else {
                            map -> spells.push_back(new HealFireZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                            }
                            break;
                        case 25: // 5*5 J+J Water+Water = WaterSpray
                            map -> spells.push_back(new WaterSpray((*pit)->get_x() + (*pit)->get_width()/2 + 2*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 2*dy*(*pit)->get_height(),dx,dy));
                            break;
                        case 5: // 5*1 J+U Water+Life
                            if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                            map -> spells.push_back(new DamageZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                            }
                            else {
                            map -> spells.push_back(new DamageZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                            }
                            break;
                        case 15: // 3*5 O+J Fire+Water
                            if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                            map -> spells.push_back(new FogZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                            }
                            else {
                            map -> spells.push_back(new FogZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                            }
                            break;
                        case 77: // 7*11 K+L Ice+Rock
                            if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                            map -> spells.push_back(new FreezeZ((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                            }
                            else {
                            map -> spells.push_back(new FreezeZ(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                            }
                            break;
                        case 1: // 1*1 U+U Life + Life = Healing beam
                            map -> spells.push_back(new HealB((*pit)->get_x() + (*pit)->get_width()/2 + 1*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 1*dy*(*pit)->get_height(),dx,dy));
                            break;
                        case 4: // 2*2 I+I Shield + Shield = Main shield
                            if (sqrt((dx1)*(dx1)+(dy1)*(dy1))>400) {
                                map -> spells.push_back(new MainShield((*pit)->get_x() - (*pit)->get_width()/2+6*dx*(*pit)->get_width(),(*pit)->get_y() - (*pit)->get_height()/2+6*dy*(*pit)->get_height()));
                            }
                            else {
                                map -> spells.push_back(new MainShield(event.mouse.x / sx + camera.get_x() - 1.5*(*pit)->get_width(), event.mouse.y / sy + camera.get_y() - 1.5*(*pit)->get_height()));
                            }
                            break;
                        
                        case 9:
                            map -> spells.push_back(new FireSpray((*pit)->get_x() + (*pit)->get_width()/2 + 2*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 2*dy*(*pit)->get_height(),dx,dy));
                            break;
                        default:

                       // } else if (std::count(elementlist.begin(),elementlist.end(),1)==1 && std::count(elementlist.begin(),elementlist.end(),2)==1) {
                       //     map -> spells.push_back(new HealZ(event.mouse.x - (*pit)->get_width()/2,event.mouse.y - (*pit)->get_height()/2));
                     //   } else if (std::count(elementlist.begin(),elementlist.end(),1)==2) {
                   //         map -> spells.push_back(new HealB((*pit)->get_x() + (*pit)->get_width()/2 + 2*dx*(*pit)->get_width(),(*pit)->get_y() + (*pit)->get_height()/2 + 2*dy*(*pit)->get_height(),dx,dy));
                            std::cout << "No spells associated to this combo of two buttons" << std::endl;
                            break;
                    }
                    // if (elementlist.size() == 2) {
                    //     if (std::count(elementlist.begin(),elementlist.end(),6)==2) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),5)==2) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),5)==1 && std::count(elementlist.begin(),elementlist.end(),1)==1) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),6)==1 && std::count(elementlist.begin(),elementlist.end(),3)==1) {
                    //     } else if (std::count(elementlist.begin(),elementlist.end(),1)==1 && std::count(elementlist.begin(),elementlist.end(),2)==1) {
                    //     } else {
                    //     }
                    // } else {
                    // }
                // define the direction vector when right-click//
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
                    //elementlist.push_back(4);
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

            map->draw_list(map->players, camera.get_x(), camera.get_y());

            map->draw_list(map->spells, camera.get_x(), camera.get_y());

            map->draw_list(map->statics, camera.get_x(), camera.get_y());

            e1p->draw();
            e2p->draw();

            al_set_target_backbuffer(disp);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            minimap->draw(map->players);
            al_flip_display();

            redraw = false;
        }

        if(!isServer){
                (*interface).send_string((*pit)->encode_player());
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
    interface = new Server(io_service, 13, &*game_status);
    while(!interface->ready){
        std::cout<<"Not yet"<<std::endl;
    }
    std::cout<<"..."<<std::endl;
    game_status->game_state=2;
}

void client_loop(Gamestatus *game_status, Interface* &interface, bool &isServer, short &client_number){
    delete interface;
    isServer = false;
    boost::asio::io_service io_service;
    interface = new Client(io_service, "129.104.198.116", "13", &*game_status);
    interface->send_string("ready");
    std::cout<<"Sent !"<<std::endl;
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
    ALLEGRO_DISPLAY* disp = al_create_display(2560, 1440); //Change this resolution to change window size
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

    must_init(al_install_audio(), "Audio addon");
    must_init(al_init_acodec_addon(), "Audio codecs addon");
    must_init(al_reserve_samples(16), "reserve samples");


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());


    Gamestatus game_status(/*game_state*/ 1, /*map pointer*/0);
    Interface* interface=new Interface();
    bool isServer=true;
    short client_number=1;
    /*
    Game state states:
    0 => End game
    1 => main menu
    2 => game loop
    3 => settings?
    4 => Create game
    5 => Join game
    */
    bool redraw = true;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);

    ALLEGRO_SAMPLE* music = al_load_sample("resources/background_music.wav");
    // must_init(music, "music");
    al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

    while (game_status.game_state != 0) {
        if (game_status.game_state == 1) {
            main_menu_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, sx, sy);
        }
        if (game_status.game_state == 2) {
            game_loop(&game_status, redraw, queue, event, timer, key, buffer, disp,
                    screenWidth, screenHeight, windowWidth, windowHeight, scaleX,
                    scaleY, scaleW, scaleH, sx, sy, interface, isServer, client_number);
        }
        if (game_status.game_state == 4){
            server_loop(&game_status, interface, isServer);
        }
        if (game_status.game_state == 5){
            client_loop(&game_status, interface, isServer, client_number);
        }
    }

    delete interface;
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(music);

    return 0;
}

// define the vector when right-clicking
int direction(int click_x, int click_y, int loc_x, int loc_y){
    return (click_y - loc_y)/(click_x - loc_x);
}