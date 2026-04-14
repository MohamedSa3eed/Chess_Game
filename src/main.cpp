#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.hpp"


const int FPS = 144;
const int FRAME_DELAY = 500 / FPS;

unsigned int frameStart;
int frameTime;

int main (int argc, char *argv[]) {

if (!Game::init()) {
    std::cerr << "Failed to initialize game" << std::endl;
    return -1;
}

  while (Game::isRunning()) {
    frameStart = SDL_GetTicks();
    Game::update();
    Game::handleEvents();
    frameTime = SDL_GetTicks() - frameStart;
    if (FRAME_DELAY > frameTime) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }
  Game::shutdown();

  return 0;
}
