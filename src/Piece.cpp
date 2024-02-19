#include "const.hpp"
#include "Game.hpp"
#include "Piece.hpp"

Piece::Piece(std::string texturePath, bool color) 
    : m_texturePath(texturePath), m_color(color) {
  m_isAlive = true;
  SDL_Surface *loadedSurface = IMG_Load(texturePath.c_str());
  m_texture = SDL_CreateTextureFromSurface(Game::getInstance().renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
}

void Piece::spawn(int x, int y) {
  m_srcRect = {x*SQUARE_SIZE, y*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  SDL_RenderCopy(Game::getInstance().renderer, m_texture, nullptr, &m_srcRect);
}

Piece::~Piece() {
  SDL_DestroyTexture(m_texture);
}
