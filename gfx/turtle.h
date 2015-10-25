#pragma once

#include "StdAfx.h"
#include "turtle.h"

class Turtle {
public:
	float x, y, angle, scale, angleScale, width;
	bool up;
	ALLEGRO_COLOR color, targetColor;
	int ttl;

	Turtle() : x(0.0f), y(0.0f), angle(0.0f), scale(1.0f), angleScale(1.0f), width(1.0f), up(false),
		       color(al_map_rgb(0,0,0)), targetColor(al_map_rgb(255,255,255)), ttl(10) {}
	/* Turtle(Turtle &turtle) :
			x(turtle.x),
			y(turtle.y),
			angle(turtle.angle),
			scale(turtle.scale),
			width(turtle.width),
			up(turtle.up),
			color(turtle.color)
		{} */

	void Forward(float);
	void Backward(float);
	void Left(float);
	void Right(float);
	bool TestTTL(void);
	void ColorStep(float);
};

