#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(bool color, int position) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_BISHOP.c_str());
    if (position == RIGHT) {
      m_xPos = WHITE_RIGHT_BISHOP_POSITION.first;
      m_yPos = WHITE_RIGHT_BISHOP_POSITION.second;
    }
    else {
      m_xPos = WHITE_LEFT_BISHOP_POSITION.first;
      m_yPos = WHITE_LEFT_BISHOP_POSITION.second;
    }
  }
  else {
    loadedSurface = IMG_Load(BLACK_BISHOP.c_str());
    if (position == RIGHT) {
      m_xPos = BLACK_RIGHT_BISHOP_POSITION.first;
      m_yPos = BLACK_RIGHT_BISHOP_POSITION.second;
    }
    else {
      m_xPos = BLACK_LEFT_BISHOP_POSITION.first;
      m_yPos = BLACK_LEFT_BISHOP_POSITION.second;
    }
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

Bishop::~Bishop() {
  SDL_DestroyTexture(m_texture);
}
