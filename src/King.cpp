#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "King.hpp"

King::King(bool color) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_KING.c_str());
    m_xPos = WHITE_KING_POSITION.first;
    m_yPos = WHITE_KING_POSITION.second;
  }
  else {
    loadedSurface = IMG_Load(BLACK_KING.c_str());
    m_xPos = BLACK_KING_POSITION.first;
    m_yPos = BLACK_KING_POSITION.second;
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

King::~King() {
  SDL_DestroyTexture(m_texture);
}
