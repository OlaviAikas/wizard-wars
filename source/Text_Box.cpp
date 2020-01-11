#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <string>

using namespace std;

float FPS=60;

int number_text_boxes=3;	// the number of textboxes 

int *switch_text_boxes;		
string *text_boxes;			
int *command_prompt;		

ALLEGRO_KEYBOARD_STATE keyboard;
ALLEGRO_FONT *font8;
ALLEGRO_MOUSE_STATE mouse;

void textbox (int coordinate_x, int coordinate_y, int number_signs, int coordinate_command_prompt, int number_text_box); 

int main()
{	
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    ALLEGRO_TIMER *timer=NULL;
    bool redraw=true;

	timer=al_create_timer(1.0/FPS);

    ALLEGRO_DISPLAY *window = al_create_display(640, 480);
    al_set_window_title (window, "Textboxes");
    font8=al_create_builtin_font ();
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(window));
    ALLEGRO_EVENT event;
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    
    switch_text_boxes=new int [number_text_boxes]; 
    for (int i=0; i<number_text_boxes; i++)
    {
    	switch_text_boxes[i]=0; // the textboxes are inactive 
    }
    
    text_boxes=new string [number_text_boxes];
    
  	command_prompt=new int [number_text_boxes];
  	for (int i=0; i<number_text_boxes; i++)
  	{
  		command_prompt[i]=25;	// the initial coordinates command prompts are the same as the coordinates x
  	}								

    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {
    	al_get_next_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
	    al_get_mouse_state(&mouse);
        al_get_keyboard_state(&keyboard);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if (ev.type==ALLEGRO_EVENT_TIMER)
        {
        	redraw=true;
        }
        else if (ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
        	break;
        }
        
        // source - start
        
        textbox(25, 25, 10, 25, 0);
        
        textbox(25, 50, 20, 25, 1);
        
        textbox(25, 75, 30, 25, 2);
       
       	// source - end
       
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw=false;
			al_flip_display();
		}
    }
    al_destroy_font(font8);
    
    al_destroy_display(window);
    return 0;
}

void textbox (int coordinate_x, int coordinate_y, int number_signs, int coordinate_command_prompt, int number_text_box)
{
	al_draw_rectangle(coordinate_x-2, coordinate_y-2, coordinate_x+8*number_signs+2, coordinate_y+10, al_map_rgba(255, 255, 255, 255), 1);	// border of the textbox
		
	if ((mouse.x>coordinate_x-2 && mouse.x<coordinate_x+8*number_signs) && (mouse.y>coordinate_y-2 && mouse.y<coordinate_y+10) && mouse.buttons==1) 
	{	
		for (int i=0; i<number_text_boxes; i++)
		{
			switch_text_boxes[i]=0;
		}
			
		switch_text_boxes[number_text_box]=1;		// activation of the textbox when press the rectangle  
			
		al_rest(0.15);					
	}

	string Signs[47]={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	if (switch_text_boxes[number_text_box]==1) 		// active the textbox
	{
		al_draw_line(command_prompt[number_text_box], coordinate_y-1, command_prompt[number_text_box], coordinate_y+8, al_map_rgba(255, 255, 255, 255), 1); // command prompt
		
		for (int i=0; i<47; i++)
		{
			if (al_key_down(&keyboard, i))
			{
				if (text_boxes[number_text_box].length()<number_signs)
				{
					text_boxes[number_text_box].insert((command_prompt[number_text_box]-coordinate_command_prompt)/8,  Signs[i-1].c_str()); 
					command_prompt[number_text_box]+=8;
					al_rest(0.15);
				}
			}
		}
		
		if (al_key_down(&keyboard, ALLEGRO_KEY_BACKSPACE))										
		{
			if (text_boxes[number_text_box].length()>0 && command_prompt[number_text_box]!=coordinate_command_prompt)																								
			{
				text_boxes[number_text_box]=text_boxes[number_text_box].erase(((command_prompt[number_text_box]-coordinate_command_prompt)/8)-1, 1);	
			}
			
			if (command_prompt[number_text_box]>coordinate_command_prompt+7)													
			{
				command_prompt[number_text_box]-=8;															
			}
			
			al_rest(0.15);
		}
		
		if (al_key_down(&keyboard, ALLEGRO_KEY_LEFT))			
		{
			if (command_prompt[number_text_box]>coordinate_command_prompt+7)				
			{
				command_prompt[number_text_box]-=8;						
			}
			al_rest(0.15);
		}
		
		if (al_key_down(&keyboard, ALLEGRO_KEY_RIGHT))					
		{
			if (command_prompt[number_text_box]<coordinate_command_prompt+8*text_boxes[number_text_box].length())	
			{
				command_prompt[number_text_box]+=8;									
			}
			al_rest(0.15);
		}
	}

	al_draw_text(font8, al_map_rgb(255, 255, 255), coordinate_x, coordinate_y, 0, text_boxes[number_text_box].c_str());	
}
