#include <iostream>

#include "const.hpp"
#include "Graphics.hpp"
#include "Piece.hpp"

Piece::Piece(bool color) 
    : m_color(color) {
  m_isAlive = true;
}

Piece::~Piece() {
  if (texture) SDL_DestroyTexture(texture);
}

bool Piece::getColor(void) {
  return m_color;
}

void Piece::spawn(int x, int y) {
    body.x = x;
    body.y = y;
}

void Piece::move(int x, int y) {
    m_xPos = x;
    m_yPos = y;
    spawn(x*SQUARE_SIZE, y*SQUARE_SIZE);
}

// #########################################################

King::King(bool color) : Piece(color) {
  if (color == WHITE) {
    texturePath = WHITE_KING;
    m_xPos = WHITE_KING_POSITION.first;
    m_yPos = WHITE_KING_POSITION.second;
  }
  else {
    texturePath = BLACK_KING;
    m_xPos = BLACK_KING_POSITION.first;
    m_yPos = BLACK_KING_POSITION.second;
  }
  body = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  texture = Graphics::getTexture(*this);
  if (!texture) {
      std::cerr << "Failed to load texture: " << texturePath << std::endl;
  }
}

bool King::isValidMove(int x, int y) {
  int dx = std::abs(x - m_xPos);
  int dy = std::abs(y - m_yPos);
  return (dx <= 1 && dy <= 1) && !(dx == 0 && dy == 0);
}

// ##########################################################

Queen::Queen(bool color) : Piece(color) {
  if (color == WHITE) {
    texturePath = WHITE_QUEEN;
    m_xPos = WHITE_QUEEN_POSITION.first;
    m_yPos = WHITE_QUEEN_POSITION.second;
  }
  else {
    texturePath = BLACK_QUEEN;
    m_xPos = BLACK_QUEEN_POSITION.first;
    m_yPos = BLACK_QUEEN_POSITION.second;
  }
  body = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  texture = Graphics::getTexture(*this);
  if (!texture) {
      std::cerr << "Failed to load texture: " << texturePath << std::endl;
  }
}

bool Queen::isValidMove(int x, int y) {
  int dx = std::abs(x - m_xPos);
  int dy = std::abs(y - m_yPos);
  return (dx == dy || dx == 0 || dy == 0) && !(dx == 0 && dy == 0);
}

// ##########################################################

Knight::Knight(bool color, int position) : Piece(color) {
  if (color == WHITE) {
    texturePath = WHITE_KNIGHT;
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
    texturePath = BLACK_KNIGHT;
    if (position == RIGHT) {
      m_xPos = BLACK_RIGHT_KNIGHT_POSITION.first;
      m_yPos = BLACK_RIGHT_KNIGHT_POSITION.second;
    }
    else {
      m_xPos = BLACK_LEFT_KNIGHT_POSITION.first;
      m_yPos = BLACK_LEFT_KNIGHT_POSITION.second;
    }
  }
  body = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  texture = Graphics::getTexture(*this);
  if (!texture) {
      std::cerr << "Failed to load texture: " << texturePath << std::endl;
  }
}

bool Knight::isValidMove(int x, int y) {
  int dx = std::abs(x - m_xPos);
  int dy = std::abs(y - m_yPos);
  return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

// ##########################################################

Bishop::Bishop(bool color, int position) : Piece(color) {
  if (color == WHITE) {
    texturePath = WHITE_BISHOP;
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
    texturePath = BLACK_BISHOP;
    if (position == RIGHT) {
      m_xPos = BLACK_RIGHT_BISHOP_POSITION.first;
      m_yPos = BLACK_RIGHT_BISHOP_POSITION.second;
    }
    else {
      m_xPos = BLACK_LEFT_BISHOP_POSITION.first;
      m_yPos = BLACK_LEFT_BISHOP_POSITION.second;
    }
  }
  body = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  texture = Graphics::getTexture(*this);
  if (!texture) {
      std::cerr << "Failed to load texture: " << texturePath << std::endl;
  }
}

bool Bishop::isValidMove(int x, int y) {
  int dx = std::abs(x - m_xPos);
  int dy = std::abs(y - m_yPos);
  return dx == dy && dx != 0;
}

// ##########################################################
Rook::Rook(bool color, int position) : Piece(color) {
  if (color == WHITE) {
    texturePath = WHITE_ROOK;
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
    texturePath = BLACK_ROOK;
    if (position == RIGHT) {
      m_xPos = BLACK_RIGHT_ROOK_POSITION.first;
      m_yPos = BLACK_RIGHT_ROOK_POSITION.second;
    }
    else {
      m_xPos = BLACK_LEFT_ROOK_POSITION.first;
      m_yPos = BLACK_LEFT_ROOK_POSITION.second;
    }
  }
  body = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  texture = Graphics::getTexture(*this);
  if (!texture) {
      std::cerr << "Failed to load texture: " << texturePath << std::endl;
  }
}

bool Rook::isValidMove(int x, int y) {
  int dx = std::abs(x - m_xPos);
  int dy = std::abs(y - m_yPos);
  return (dx == 0 && dy != 0) || (dx != 0 && dy == 0);
}

// ##########################################################

Pawn::Pawn(bool color, int id) : Piece(color) {
  if (color == WHITE) {
    texturePath = WHITE_PAWN;
    m_xPos = WHITE_PAWN_POSITIONS[id].first;
    m_yPos = WHITE_PAWN_POSITIONS[id].second;
  }
  else {
    texturePath = BLACK_PAWN;
    m_xPos = BLACK_PAWN_POSITIONS[id].first;
    m_yPos = BLACK_PAWN_POSITIONS[id].second;
  }
  body = {m_xPos*SQUARE_SIZE, m_yPos*SQUARE_SIZE, PIECE_SIZE, PIECE_SIZE};
  texture = Graphics::getTexture(*this);
  if (!texture) {
      std::cerr << "Failed to load texture: " << texturePath << std::endl;
  }
}

bool Pawn::isValidMove(int x, int y) {
  int dx = std::abs(x - m_xPos);
  int dy = y - m_yPos; // Pawns move forward, so we check the direction
  if (m_color == WHITE) {
    return (dx == 0 && dy == -1) || (dx == 0 && dy == -2 && m_yPos == 6) || (dx == 1 && dy == -1); // Move forward or capture
  } else {
    return (dx == 0 && dy == 1) || (dx == 0 && dy == 2 && m_yPos == 1) || (dx == 1 && dy == 1); // Move forward or capture
  }
}

