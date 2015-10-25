#include "StdAfx.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include "draw.h"
#include "turtle.h"

unsigned short c = 90;
int seed = time(0);

std::vector<std::function<void(ALLEGRO_BITMAP*)>> Layers;

void lsystem(Turtle rzuf, char symbol){
	if(rzuf.TestTTL()) {
		if(probability(0.3f)) {
			ALLEGRO_COLOR col = al_map_rgb(250, 10, 40);
			col.a = 0.7f * rzuf.color.a;
			al_draw_filled_rectangle(rzuf.x-1.5f, rzuf.y-1.5f, rzuf.x+1.5f, rzuf.y+1.5f, col);
			//al_draw_filled_circle(rzuf.x, rzuf.y, 2.0f, col);
		}
		return;
	}

	rzuf.ColorStep(1.0f / 16);

	switch(symbol) {
	case 'a':
		rzuf.scale *= 0.7f;
		rzuf.Left(40.0f);
		rzuf.Forward(24.0f);

		lsystem(rzuf, 'b');
		lsystem(rzuf, 'c');

		rzuf.angleScale *= -0.67f;
		rzuf.scale *= 0.5f;

		if(probability(0.8f)) {
			lsystem(rzuf, 'b');
			lsystem(rzuf, 'c');
		}
		break;
	case 'b':
		rzuf.scale *= 0.7f;
		rzuf.Left(12.0f);
		rzuf.Forward(7.0f);

		if(probability(0.8f))
			lsystem(rzuf, 'a');
		else {
			rzuf.scale *= (sin(randF(-1.0f) * M_PI_2) + 1.0f) * 2;
			lsystem(rzuf, 'b');
		}
		break;
	case 'c':
		rzuf.Right(randF(30.0f) + 30.0f);
		rzuf.Forward(10.0f);
		lsystem(rzuf, 'a');

		if(probability(0.4f)) {
			rzuf.Right(36.0f);
			rzuf.angleScale *= -1;
			rzuf.scale *= 0.8f;
			lsystem(rzuf, 'b');
		}
		break;
	default:
		rzuf.Forward(32.0f);

		Turtle rzuf2(rzuf);
		rzuf2.Left(randF(30.0f) - 15.0f);
		rzuf2.scale *= 0.5f;
		if(probability(0.67f)) rzuf2.angleScale *= -1;
		lsystem(rzuf2, 'd');

		rzuf2 = rzuf;
		rzuf2.Left(95.0f);
		rzuf2.scale *= 0.3f;
		lsystem(rzuf2, 'a');

		lsystem(rzuf, 'a');
		rzuf.angleScale = randF(-0.5f) - 0.5f;
		lsystem(rzuf, 'a');

		return;
	}
}// */

void tree(Turtle rzuf) {
	while(!rzuf.TestTTL()) {
		rzuf.Right( randF(100.0f) - 50.0f );
		rzuf.angle *= 0.85f;
		//rzuf.scale *= 0.99f;
		rzuf.Forward(1);
		while(probability(0.3f)) {
			rzuf.scale *= M_SQRT1_2;
			tree(rzuf);
		}
	}
	
	if(probability(0.3f)) {
		ALLEGRO_COLOR col = al_map_rgb(250, 240, 40);
		col.a = 0.7f * rzuf.color.a;
		al_draw_filled_rectangle(rzuf.x-1.0f, rzuf.y-1.0f, rzuf.x+1.0f, rzuf.y+1.0f, col);
	}
}

ALLEGRO_BITMAP *buffer;
bool setup(ALLEGRO_DISPLAY* display) {
	Layers.push_back([](ALLEGRO_BITMAP* buf){
		int w = al_get_bitmap_width(buf);
		int h = al_get_bitmap_height(buf);
		al_set_target_bitmap(buf);
		
		for(int i=0; i>=0; --i) {
			for(float ans = 0.2f; ans <= 1.0f; ans += 0.2f) {
				Turtle rzuf;
				{
					rzuf.color = al_map_rgb(160, 160, 160);
					rzuf.targetColor = al_map_rgb(180, 200, 100);
					rzuf.ColorStep(ans);
					rzuf.targetColor = rzuf.color;
					register float nans = 1.0f - ans;
					rzuf.color = al_map_rgb(nans, nans, nans);
					rzuf.color.a = (12.0f - i) / 12;
				}
				rzuf.scale = 5;
				rzuf.width = 7;
				rzuf.x = randF(w);
				rzuf.y = h + 107 - (10 * i);
				rzuf.ttl = 30;
				rzuf.angleScale = ans;

				lsystem(rzuf, 'd');
			}
		}
	});
	Layers.push_back([](ALLEGRO_BITMAP* buf){
		int w = al_get_bitmap_width(buf);
		int h = al_get_bitmap_height(buf);
		al_set_target_bitmap(buf);

		ALLEGRO_COLOR fog = al_map_rgba(192, 224, 255, 8);
		for(int i=9; i>=0; --i) {
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
			Turtle rzuf;
			rzuf.ttl = INT_MAX;
			rzuf.x = randF(w);
			rzuf.y = h - (10 * i) + 53.5f;
			rzuf.width = 0.6f;
			rzuf.scale = 37 - i;
			rzuf.color = al_map_rgb(20, 10, 1);
			tree(rzuf);
			tree(rzuf);

			al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
			al_draw_filled_rectangle(0, 0, w, h, fog);
		}
	});
	al_add_new_bitmap_flag(ALLEGRO_MEMORY_BITMAP);
	buffer = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));
	return true;
}

void draw(ALLEGRO_DISPLAY* display) {
	c = (c + 1) % 360;
	/*
	float fc = (cos(M_PI * c / 180) + 1) / 2;
	unsigned char r = (unsigned char)( fc * 255 );
	fc = sin(fc * M_PI_2);
	unsigned char b = (unsigned char)( fc * 255 );
	unsigned char g = (unsigned char)( (
			((unsigned short)r) + ((unsigned short)b) * 2
	) / 3 );
	al_clear_to_color(al_map_rgb(r, g, b));
	*/
	
	//mt_srand(seed);
	ALLEGRO_BITMAP* backbuffer = al_get_backbuffer(display);
	for(auto it=Layers.begin(); it != Layers.end(); ++it)
		(*it)(buffer);
	al_set_target_bitmap(backbuffer);
	al_draw_bitmap(buffer, 0.0f, 0.0f, 0);
}
