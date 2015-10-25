#include "StdAfx.h"
#include <stdio.h>
// #include <allegro5/allegro_windows.h>
#include "draw.h"

bool done;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display = NULL;


bool init(int w, int h, bool fullscreen = false) {
//	HWND hWndDisplay = NULL;
	const char* err;
	#define INIT(x, y) if(!(x)) { err = y; goto err; }

	mt_seed();
	
	// Allegro initialization

	INIT( al_init() &&
	      al_install_mouse() &&
	      al_install_keyboard() &&
	      al_init_image_addon() &&
		  al_init_primitives_addon(),
		"initialize allegro" );
	
	
	if(fullscreen) al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	INIT(display = al_create_display(w, h), "create display")
	al_set_window_title(display, "åwiteü");
//	{	auto icon = al_load_bitmap("img\\icon.gif");
//		if(icon) al_set_display_icon(display, icon);	}
//	if(fullscreen) {
//		hWndDisplay = al_get_win_window_handle(display);
//		SetWindowLong(hWndDisplay, GWL_STYLE, 0);
//		ShowWindow(hWndDisplay, SW_MAXIMIZE);
//	}


	INIT(timer = al_create_timer(1.0 / 60), "create timer")

    INIT(event_queue = al_create_event_queue(), "create event queue")

	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

	// End of Allegro initialization

	INIT(setup(display), "initialize renderer");

	#undef INIT
	return true;

err:
	if(display) al_destroy_display(display);
	{
		char* buf = new char[strlen(err) + 13];
		sprintf(buf, "Failed to %s!\n", err);
//		MessageBoxA(NULL, buf, "Error", MB_ICONERROR);
		delete buf;
	}
	return false;
}

void deinit() {
	al_destroy_display(display);
}

void game_loop(void)
{
    bool redraw = true;
    al_start_timer(timer);
 
    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

		switch(event.type)
		{
		case ALLEGRO_EVENT_TIMER:
            redraw = true;
			break;
		
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return;

		case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				return;
			break;
        }
 

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
			draw(display);
            al_flip_display();
        }
    }
}

int main(int argc, char **argv)
{
	if(!init(1366, 768, true))
		return -1;

	game_loop();
 
	deinit();
	return 0;
}
