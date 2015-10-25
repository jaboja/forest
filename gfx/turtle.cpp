#include "StdAfx.h"
#include "turtle.h"

void Turtle::Forward(float distance) {
	distance *= scale;
	float radAngle = angle * M_PI_4 / 45;
	float nx = x + sin(radAngle) * distance;
	float ny = y - cos(radAngle) * distance;

	if(!up) {
		float w = width * scale;
		if(w > 2.5f) {
			al_draw_filled_circle(x, y, w / 2, color);
			al_draw_filled_circle(nx, ny, w / 2, color);
		}
		al_draw_line(x, y, nx, ny, color, w);
	}

	x = nx; y = ny;
}

void Turtle::Backward(float distance) {
	Forward(-distance);
}

void Turtle::Left(float _angle) {
	angle -= _angle * angleScale;
}

void Turtle::Right(float _angle) {
	angle += _angle * angleScale;
}

bool Turtle::TestTTL(void) {
	if(--ttl < 0) return true;

	return (width * scale) < 1.0f;
}

void Turtle::ColorStep(float amout) {
	float amoutDiff = 1.0f - amout;

	#define COLOR_MOD(a,b) a = a * amoutDiff + b * amout;
	COLOR_MOD(color.r, targetColor.r);
	COLOR_MOD(color.g, targetColor.g);
	COLOR_MOD(color.b, targetColor.b);
	#undef COLOR_MOD
}
// */