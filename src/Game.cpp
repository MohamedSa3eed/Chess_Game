#include <iostream>
#include <map>

#include "Game.hpp"
#include "Graphics.hpp"
#include "const.hpp"
#include "Piece.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

SDL_Event Game::m_event;
bool Game::m_isRunning = false;
bool Game::turn = WHITE;
Piece* Game::draggingPiece = nullptr;
// Chessboard
// 0,0  1,0  2,0  3,0  4,0  5,0  6,0  7,0
//
// 0,1  1,1  2,1  3,1  4,1  5,1  6,1  7,1
//
// 0,2  1,2  2,2  3,2  4,2  5,2  6,2  7,2
//
// 0,3  1,3  2,3  3,3  4,3  5,3  6,3  7,3
//
// 0,4  1,4  2,4  3,4  4,4  5,4  6,4  7,4
//
// 0,5  1,5  2,5  3,5  4,5  5,5  6,5  7,5
//
// 0,6  1,6  2,6  3,6  4,6  5,6  6,6  7,6
//
// 0,7  1,7  2,7  3,7  4,7  5,7  6,7  7,7
std::map<std::pair<int, int>, Piece *> Game::board = {
    {{0, 0}, nullptr}, {{0, 1}, nullptr}, {{0, 2}, nullptr}, {{0, 3}, nullptr},
    {{0, 4}, nullptr}, {{0, 5}, nullptr}, {{0, 6}, nullptr}, {{0, 7}, nullptr},
    {{1, 0}, nullptr}, {{1, 1}, nullptr}, {{1, 2}, nullptr}, {{1, 3}, nullptr},
    {{1, 4}, nullptr}, {{1, 5}, nullptr}, {{1, 6}, nullptr}, {{1, 7}, nullptr},
    {{2, 0}, nullptr}, {{2, 1}, nullptr}, {{2, 2}, nullptr}, {{2, 3}, nullptr},
    {{2, 4}, nullptr}, {{2, 5}, nullptr}, {{2, 6}, nullptr}, {{2, 7}, nullptr},
    {{3, 0}, nullptr}, {{3, 1}, nullptr}, {{3, 2}, nullptr}, {{3, 3}, nullptr},
    {{3, 4}, nullptr}, {{3, 5}, nullptr}, {{3, 6}, nullptr}, {{3, 7}, nullptr},
    {{4, 0}, nullptr}, {{4, 1}, nullptr}, {{4, 2}, nullptr}, {{4, 3}, nullptr},
    {{4, 4}, nullptr}, {{4, 5}, nullptr}, {{4, 6}, nullptr}, {{4, 7}, nullptr},
    {{5, 0}, nullptr}, {{5, 1}, nullptr}, {{5, 2}, nullptr}, {{5, 3}, nullptr},
    {{5, 4}, nullptr}, {{5, 5}, nullptr}, {{5, 6}, nullptr}, {{5, 7}, nullptr},
    {{6, 0}, nullptr}, {{6, 1}, nullptr}, {{6, 2}, nullptr}, {{6, 3}, nullptr},
    {{6, 4}, nullptr}, {{6, 5}, nullptr}, {{6, 6}, nullptr}, {{6, 7}, nullptr},
    {{7, 0}, nullptr}, {{7, 1}, nullptr}, {{7, 2}, nullptr}, {{7, 3}, nullptr},
    {{7, 4}, nullptr}, {{7, 5}, nullptr}, {{7, 6}, nullptr}, {{7, 7}, nullptr},
};

bool Game::init() {
  m_isRunning = true;

  if (!Graphics::init()) {
    m_isRunning = false;
    return false;
  }

  auto placePiece = [&](Piece *piece) {
    board[{piece->body.x/SQUARE_SIZE, piece->body.y/SQUARE_SIZE}] = piece;
  };

  placePiece(new King(WHITE));
  placePiece(new King(BLACK));
  placePiece(new Queen(WHITE));
  placePiece(new Queen(BLACK));
  placePiece(new Bishop(WHITE, LEFT));
  placePiece(new Bishop(WHITE, RIGHT));
  placePiece(new Bishop(BLACK, LEFT));
  placePiece(new Bishop(BLACK, RIGHT));
  placePiece(new Knight(WHITE, LEFT));
  placePiece(new Knight(WHITE, RIGHT));
  placePiece(new Knight(BLACK, LEFT));
  placePiece(new Knight(BLACK, RIGHT));
  placePiece(new Rook(WHITE, LEFT));
  placePiece(new Rook(WHITE, RIGHT));
  placePiece(new Rook(BLACK, LEFT));
  placePiece(new Rook(BLACK, RIGHT));

  for (int i = 0; i < CHESSBOARD_SIZE; ++i) {
    placePiece(new Pawn(WHITE, i));
    placePiece(new Pawn(BLACK, i));
  }

  return true;
}

void Game::handleEvents() {
  static int oldX, oldY;
  static int offsetX, offsetY;
  static bool isDragging = false;
  static Piece *piece = nullptr;
  SDL_WaitEvent(&m_event);
  switch (m_event.type) {
  case SDL_QUIT:
    m_isRunning = false;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (m_event.button.button == SDL_BUTTON_LEFT) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      int boardX = mouseX / SQUARE_SIZE;
      int boardY = mouseY / SQUARE_SIZE;
      if (boardX >= 0 && boardX < CHESSBOARD_SIZE && boardY >= 0 && boardY < CHESSBOARD_SIZE) {
        piece = board[{boardX, boardY}];
        if (piece && piece->getColor() == turn) {
          board[{boardX, boardY}] = nullptr;
          oldX = boardX;
          oldY = boardY;
          offsetX = mouseX - piece->body.x;
          offsetY = mouseY - piece->body.y;
          isDragging = true;
          draggingPiece = piece;
        }
      }
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (m_event.button.button == SDL_BUTTON_LEFT && isDragging && piece) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      int newX = mouseX / SQUARE_SIZE;
      int newY = mouseY / SQUARE_SIZE;
      if (newX >= 0 && newX < CHESSBOARD_SIZE && newY >= 0 && newY < CHESSBOARD_SIZE) {
        // TODO Add move validation here (e.g., isValidMove(piece, oldX, oldY, newX, newY))
        Piece *target = board[{newX, newY}];
        if (target) delete target;  // Handle capture
        board[{newX, newY}] = piece;
        piece->body.x = newX * SQUARE_SIZE;
        piece->body.y = newY * SQUARE_SIZE;
        toggleTurn();
      } else {
        // Invalid drop: return to original position
        board[{oldX, oldY}] = piece;
        piece->body.x = oldX * SQUARE_SIZE;
        piece->body.y = oldY * SQUARE_SIZE;
      }
      isDragging = false;
      piece = nullptr;
      draggingPiece = nullptr;
    }
    break;
  case SDL_MOUSEMOTION:
    if (isDragging && piece) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      piece->body.x = mouseX - offsetX;
      piece->body.y = mouseY - offsetY;
    }
    break;
  default:
    break;
  }
}

void Game::update() {
  Graphics::clear();
  Graphics::drawChessBoard();
  for (const auto& entry : board) {
    if (entry.second != nullptr) {
      Graphics::drawPiece(*entry.second);
    }
  }
  if (draggingPiece) {
    Graphics::drawPiece(*draggingPiece);
  }
  Graphics::present();
}

bool Game::isRunning() { 
  return m_isRunning;
}

void Game::shutdown() {
  for (const auto& entry : board) {
    delete entry.second;
  }
  Graphics::cleanup();
}

void Game::toggleTurn() {
  Game::turn = (Game::turn == WHITE) ? BLACK : WHITE;
}
