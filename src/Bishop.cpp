#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(bool color) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_BISHOP.c_str());
  }
  else {
    loadedSurface = IMG_Load(BLACK_BISHOP.c_str());
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);

}

Bishop::~Bishop() {

}
