#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <vector>

#include "Piece.hpp"

class Game
{
  public: 
    static std::map<std::pair<int, int>, Piece*> board;
    
    Game(void) = default;
    ~Game(void) = default;

    static bool init(void);
    static void shutdown(void);
    static void update(void);
    static bool isRunning(void);

  private:
    struct MoveRecord {
      Piece* piece;
      int fromX;
      int fromY;
      int toX;
      int toY;
      Piece* captured;
      bool isCastling = false;
      Piece* castlingRook = nullptr;
      int castlingRookFromX = -1;
      int castlingRookFromY = -1;
      int castlingRookToX = -1;
      int castlingRookToY = -1;
    };

    static std::vector<std::pair<int,int>> highlightedMoves;
    static std::vector<MoveRecord> moveHistory;
    static bool m_isRunning;
    static SDL_Event m_event;
    static bool turn;
    static Piece* draggingPiece;
    static std::pair<int, int> whiteKingPos;
    static std::pair<int, int> blackKingPos;

    static void toggleTurn(void);
    static void handleEvents(void);
    static void undoLastMove(void);
    static bool isPathClear(int fromX, int fromY, int toX, int toY);
    static bool isLegalMove(Piece* piece, int fromX, int fromY, int toX, int toY);
    static bool isSquareUnderAttack(int x, int y, bool byColor);
    static bool wouldLeaveKingInCheck(Piece* piece, int fromX, int fromY, int toX, int toY);
    static std::pair<int, int> getKingPosition(bool color);
    static bool isCastlingLegal(Piece* piece, int fromX, int fromY, int toX, int toY, Piece*& outRook, int& outRookFromX, int& outRookFromY, int& outRookToX, int& outRookToY);
    static void executeCastling(Piece* piece, int toX, int toY, Piece* rook, int rookFromX, int rookFromY, int rookToX, int rookToY);
};
