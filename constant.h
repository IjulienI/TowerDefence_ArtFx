#ifndef CONSTANT_H
#define CONSTANT_H

#include <raylib.h>

//BASE

const Vector2 WINDOW_SIZE = { 1080,720 };
const int FRAME_LIMIT = 144;
const Color BACKGROUND_COLORATION = BLACK;
const int PIXELS_PER_METER = 5;


//TILES

const int TILE_SIZE = 64;
const Vector2 TILE_NUM = { (int)(WINDOW_SIZE.x / TILE_SIZE), (int)(WINDOW_SIZE.y / TILE_SIZE) };
const Vector2 TILE_SPACER = {(TILE_SIZE * 0.875) / 2,(TILE_SIZE * 0.25) / 2};// Je sors pas les chiffres au pif, j'ai calculé mais je savais pas comment récupérer seulement décimales...


//GUI
const Vector2 GUI_BUTTON_SIZE = { 100,50 };

#endif