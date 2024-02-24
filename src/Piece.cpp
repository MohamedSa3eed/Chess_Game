#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"

Piece::Piece(bool color) 
    : m_color(color) {
  m_isAlive = true;
}

void Piece::spawn(void) {
  m_srcRect = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  SDL_RenderCopy(Game::getInstance().renderer, m_texture, nullptr, &m_srcRect);
  Game::board[{m_xPos, m_yPos}] = this;
}

int Piece::getX(void) {
  return m_xPos;
}

int Piece::getY(void) {
  return m_yPos;
}

void Piece::setX(int x) {
  m_xPos = x;
}

void Piece::setY(int y) {
  m_yPos = y;
}

Piece::~Piece() {

}
