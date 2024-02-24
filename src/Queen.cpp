#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Queen.hpp"

Queen::Queen(bool color) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_QUEEN.c_str());
    m_xPos = WHITE_QUEEN_POSITION.first;
    m_yPos = WHITE_QUEEN_POSITION.second;
  }
  else {
    loadedSurface = IMG_Load(BLACK_QUEEN.c_str());
    m_xPos = BLACK_QUEEN_POSITION.first;
    m_yPos = BLACK_QUEEN_POSITION.second;
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

Queen::~Queen() {
  SDL_DestroyTexture(m_texture);
}
