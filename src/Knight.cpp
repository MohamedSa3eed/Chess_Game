#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Knight.hpp"

Knight::Knight(bool color, int position) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_KNIGHT.c_str());
    if (position == RIGHT) {
      m_xPos = WHITE_RIGHT_KNIGHT_POSITION.first;
      m_yPos = WHITE_RIGHT_KNIGHT_POSITION.second;
    }
    else {
      m_xPos = WHITE_LEFT_KNIGHT_POSITION.first;
      m_yPos = WHITE_LEFT_KNIGHT_POSITION.second;
    }
  }
  else {
    loadedSurface = IMG_Load(BLACK_KNIGHT.c_str());
    if (position == RIGHT) {
      m_xPos = BLACK_RIGHT_KNIGHT_POSITION.first;
      m_yPos = BLACK_RIGHT_KNIGHT_POSITION.second;
    }
    else {
      m_xPos = BLACK_LEFT_KNIGHT_POSITION.first;
      m_yPos = BLACK_LEFT_KNIGHT_POSITION.second;
    }
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

Knight::~Knight() {
  SDL_DestroyTexture(m_texture);
}
