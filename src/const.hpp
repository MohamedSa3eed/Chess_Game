#ifndef CONST_HPP
#define CONST_HPP

#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HIGHT = 640;
const int CHESSBOARD_SIZE = 8;
const int SQUARE_SIZE = WINDOW_WIDTH / CHESSBOARD_SIZE;
const SDL_Color lightColor = {240, 240, 220, 255};
const SDL_Color darkColor = {139, 69, 19, 255};

#endif
