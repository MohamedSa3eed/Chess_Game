#include <map>
#include <vector>
#include <algorithm>

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
std::vector<std::pair<int,int>> Game::highlightedMoves;
std::vector<Game::MoveRecord> Game::moveHistory;
std::pair<int, int> Game::whiteKingPos = {4, 7};
std::pair<int, int> Game::blackKingPos = {4, 0};
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

bool Game::isPathClear(int fromX, int fromY, int toX, int toY) {
  int dx = toX - fromX;
  int dy = toY - fromY;
  int steps = std::max(std::abs(dx), std::abs(dy));
  if (steps <= 1) return true; // adjacent or same, no path to check
  int stepX = dx / steps;
  int stepY = dy / steps;
  for (int i = 1; i < steps; ++i) {
    int checkX = fromX + i * stepX;
    int checkY = fromY + i * stepY;
    if (board[{checkX, checkY}] != nullptr) return false;
  }
  return true;
}

bool Game::isLegalMove(Piece* piece, int fromX, int fromY, int toX, int toY) {
  if (fromX == toX && fromY == toY) return false;
  if (!piece->isValidMove(toX, toY)) return false;
  if (dynamic_cast<Knight*>(piece) == nullptr && !isPathClear(fromX, fromY, toX, toY)) return false;

  Piece* target = board[{toX, toY}];
  bool isPawn = dynamic_cast<Pawn*>(piece) != nullptr;
  bool isDiagonal = std::abs(toX - fromX) == 1 && std::abs(toY - fromY) == 1;

  if (target) {
    if (target->getColor() == piece->getColor()) return false;
    if (isPawn && !isDiagonal) return false;
  } else {
    if (isPawn && isDiagonal) return false;
  }

  if (wouldLeaveKingInCheck(piece, fromX, fromY, toX, toY)) return false;
  return true;
}

std::pair<int, int> Game::getKingPosition(bool color) {
  return color == WHITE ? whiteKingPos : blackKingPos;
}

bool Game::isSquareUnderAttack(int x, int y, bool byColor) {
  for (const auto& entry : board) {
    Piece* p = entry.second;
    if (!p || p->getColor() != byColor) continue;
    
    int fromX = entry.first.first;
    int fromY = entry.first.second;
    
    if (p->isValidMove(x, y)) {
      if (dynamic_cast<Knight*>(p)) return true;
      if (isPathClear(fromX, fromY, x, y)) return true;
    }
  }
  return false;
}

bool Game::wouldLeaveKingInCheck(Piece* piece, int fromX, int fromY, int toX, int toY) {
  Piece* target = board[{toX, toY}];
  
  board[{fromX, fromY}] = nullptr;
  board[{toX, toY}] = piece;
  
  std::pair<int, int> kingPos;
  if (dynamic_cast<King*>(piece)) {
    kingPos = {toX, toY};
  } else {
    kingPos = getKingPosition(piece->getColor());
  }
  
  bool inCheck = isSquareUnderAttack(kingPos.first, kingPos.second, !piece->getColor());
  
  board[{fromX, fromY}] = piece;
  board[{toX, toY}] = target;
  
  return inCheck;
}

void Game::undoLastMove() {
  if (moveHistory.empty()) return;
  MoveRecord lastMove = moveHistory.back();
  moveHistory.pop_back();

  board[{lastMove.toX, lastMove.toY}] = nullptr;
  board[{lastMove.fromX, lastMove.fromY}] = lastMove.piece;
  lastMove.piece->move(lastMove.fromX, lastMove.fromY);

  if (lastMove.captured) {
    board[{lastMove.toX, lastMove.toY}] = lastMove.captured;
    lastMove.captured->move(lastMove.toX, lastMove.toY);
  }

  // Revert king position if king moved
  if (dynamic_cast<King*>(lastMove.piece)) {
    if (lastMove.piece->getColor() == WHITE) {
      whiteKingPos = {lastMove.fromX, lastMove.fromY};
    } else {
      blackKingPos = {lastMove.fromX, lastMove.fromY};
    }
  }

  toggleTurn();
  highlightedMoves.clear();
}

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
          highlightedMoves.clear();
          for (int x = 0; x < CHESSBOARD_SIZE; ++x) {
            for (int y = 0; y < CHESSBOARD_SIZE; ++y) {
              if (isLegalMove(piece, oldX, oldY, x, y)) {
                highlightedMoves.emplace_back(x, y);
              }
            }
          }
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
      Piece *target = nullptr;
      bool validMove = false;
      if (newX >= 0 && newX < CHESSBOARD_SIZE && newY >= 0 && newY < CHESSBOARD_SIZE && isLegalMove(piece, oldX, oldY, newX, newY)) {
        target = board[{newX, newY}];
        validMove = true;
      }

      if (validMove) {
        MoveRecord move = {piece, oldX, oldY, newX, newY, target};
        board[{oldX, oldY}] = nullptr;
        board[{newX, newY}] = piece;
        piece->move(newX, newY);
        if (target) {
          board[{newX, newY}] = piece;
        }
        // Update king position if king moved
        if (dynamic_cast<King*>(piece)) {
          if (piece->getColor() == WHITE) {
            whiteKingPos = {newX, newY};
          } else {
            blackKingPos = {newX, newY};
          }
        }
        moveHistory.push_back(move);
        toggleTurn();
      } else {
        board[{oldX, oldY}] = piece;
        piece->move(oldX, oldY);
      }

      highlightedMoves.clear();
      isDragging = false;
      piece = nullptr;
      draggingPiece = nullptr;
    }
    break;
  case SDL_MOUSEMOTION:
    if (isDragging && piece) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      piece->spawn(mouseX - offsetX, mouseY - offsetY);
    }
    break;
  case SDL_KEYDOWN:
    if ((m_event.key.keysym.mod & KMOD_CTRL) && m_event.key.keysym.sym == SDLK_z) {
      undoLastMove();
    }
    break;
  default:
    break;
  }
}

void Game::update() {
  Graphics::clear();
  Graphics::drawChessBoard();
  for (const auto& coord : highlightedMoves) {
    Piece* target = board[{coord.first, coord.second}];
    Graphics::drawHighlightSquare(coord.first, coord.second,
      target ? captureColor : moveColor);
  }
  for (const auto& entry : board) {
    if (entry.second != nullptr) {
      Graphics::drawPiece(*entry.second);
    }
  }
  if (draggingPiece) {
    Graphics::drawPiece(*draggingPiece);
  }
  Graphics::present();
  handleEvents();
}

bool Game::isRunning() { 
  return m_isRunning;
}

void Game::shutdown() {
  for (const auto& entry : board) {
    delete entry.second;
  }
  for (const auto& record : moveHistory) {
    if (record.captured) {
      delete record.captured;
    }
  }
  if (draggingPiece) {
    delete draggingPiece;
  }
  Graphics::cleanup();
}

void Game::toggleTurn() {
  Game::turn = (Game::turn == WHITE) ? BLACK : WHITE;
}
