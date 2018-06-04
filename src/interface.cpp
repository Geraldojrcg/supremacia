#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main(){
    ALLEGRO_DISPLAY * display;
    ALLEGRO_FONT * font;
	ALLEGRO_EVENT_QUEUE *queue;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();

    display  = al_create_display(640,480);
    font = al_load_ttf_font("../font/YARDSALE.ttf", 64, 0);
    queue = al_create_event_queue();

    al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    
    while (running) {
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_text(font, al_map_rgb(0,0,0),0,0,0, "HELLO WORLD");
        al_flip_display();

        ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
    }

    al_destroy_display(display);
    al_destroy_font(font);
    al_uninstall_keyboard();
    
    return 0;
}
