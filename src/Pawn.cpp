#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"

Pawn::Pawn(bool color, int id) : Piece(color) {
  SDL_Surface* loadedSurface = nullptr;
  if (color == WHITE) {
    loadedSurface = IMG_Load(WHITE_PAWN.c_str());
    m_xPos = WHITE_PAWN_POSITIONS[id].first;
    m_yPos = WHITE_PAWN_POSITIONS[id].second;
  }
  else {
    loadedSurface = IMG_Load(BLACK_PAWN.c_str());
    m_xPos = BLACK_PAWN_POSITIONS[id].first;
    m_yPos = BLACK_PAWN_POSITIONS[id].second;
  }
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

Pawn::~Pawn() {
  SDL_DestroyTexture(m_texture);
}
