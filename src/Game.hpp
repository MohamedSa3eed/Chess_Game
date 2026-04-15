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
    static std::vector<std::pair<int,int>> highlightedMoves;
    static bool m_isRunning;
    static SDL_Event m_event;
    static bool turn;
    static Piece* draggingPiece;

    static void toggleTurn(void);
    static void handleEvents(void);
    static bool isPathClear(int fromX, int fromY, int toX, int toY);
    static bool isLegalMove(Piece* piece, int fromX, int fromY, int toX, int toY);
};
