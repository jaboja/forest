#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
// #include <Windows.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "mtrand.h"

inline bool probability(float p) {
	return mt_rand() < int(p * MT_RAND_MAX);
}

inline float randF(float max) {
	return ((float) mt_rand () * max / (float) MT_RAND_MAX);
}
