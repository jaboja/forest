#!/bin/sh
g++ *.cpp -std=c++11 $(pkg-config --libs allegro-5.0 allegro_main-5.0 allegro_primitives-5.0 allegro_image-5.0)
