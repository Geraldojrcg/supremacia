#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

void run_action_display(ALLEGRO_FONT * font){
    al_draw_filled_rounded_rectangle(0, 460, 800, 600, 20, 20, al_map_rgb(255, 200, 10));
    al_draw_text(font, al_map_rgb(0,0,0),0,480,0, "Ações:");
}
void run_map_display(){
    al_draw_filled_rounded_rectangle(0, 0, 800, 456, 20, 20, al_map_rgb(0, 255, 100));
    int space = 60;
    for(int i =0; i <8; i++){
        for(int j =0; j <8; j++){
            //al_draw_filled_rounded_rectangle(10+(i*space), 10+(j*space), 60, 60, 2, 2, al_map_rgb(0, 255, 255));
        al_draw_rectangle(20+(i*space), 20+(j*space), 100, 100, al_map_rgb(0, 0, 0), 1);
        }
    }
}
void run_info_display(ALLEGRO_FONT * font){
    al_draw_filled_rounded_rectangle(680, 10, 790, 445, 20, 20, al_map_rgb(0, 200, 255));
    al_draw_text(font, al_map_rgb(0,0,0),700,50,0, "Info:");
}
int main(){
    ALLEGRO_DISPLAY * display;
    ALLEGRO_FONT * font;
	ALLEGRO_EVENT_QUEUE *queue;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    display  = al_create_display(800,600);
    font = al_load_ttf_font("../font/YARDSALE.ttf", 18, 0);
    queue = al_create_event_queue();

    al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    bool infoop = false;
    while (running){
        al_clear_to_color(al_map_rgb(255,255,255));
        run_map_display();
        run_action_display(font);
        //run_info_display(font);
        al_flip_display();

        ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
             infoop = true;
        }
        if(infoop){
            run_info_display(font);
            al_flip_display();
        }
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			running = false;
        }
    }

    al_destroy_display(display);
    al_destroy_font(font);
    al_uninstall_keyboard();
    
    return 0;
}
