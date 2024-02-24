#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(bool color, int position) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_ROOK.c_str());
    if (position == RIGHT) {
      m_xPos = WHITE_RIGHT_ROOK_POSITION.first;
      m_yPos = WHITE_RIGHT_ROOK_POSITION.second;
    }
    else {
      m_xPos = WHITE_LEFT_ROOK_POSITION.first;
      m_yPos = WHITE_LEFT_ROOK_POSITION.second;
    }
  }
  else {
    loadedSurface = IMG_Load(BLACK_ROOK.c_str());
    if (position == RIGHT) {
      m_xPos = BLACK_RIGHT_ROOK_POSITION.first;
      m_yPos = BLACK_RIGHT_ROOK_POSITION.second;
    }
    else {
      m_xPos = BLACK_LEFT_ROOK_POSITION.first;
      m_yPos = BLACK_LEFT_ROOK_POSITION.second;
    }
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

Rook::~Rook() {
  SDL_DestroyTexture(m_texture);
}
