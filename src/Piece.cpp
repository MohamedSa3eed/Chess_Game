#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"

Piece::Piece(bool color) 
    : m_color(color) {
  m_isAlive = true;
}

void Piece::spawn(int x, int y) {
  m_srcRect = {x*SQUARE_SIZE, y*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  SDL_RenderCopy(Game::getInstance().renderer, m_texture, nullptr, &m_srcRect);
}

Piece::~Piece() {
  SDL_DestroyTexture(m_texture);
}
