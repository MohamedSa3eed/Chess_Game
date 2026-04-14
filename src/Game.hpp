#pragma once

#include <SDL2/SDL.h>
#include <map>

#include "Piece.hpp"

class Game
{
  public: 
    static std::map<std::pair<int, int>, Piece*> board;

    static bool init(void);
    static void shutdown(void);
    static void handleEvents(void);
    static void update(void);
    static bool isRunning(void);
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
    
    Game(void) = default;
    ~Game(void) = default;

  private:
    static void toggleTurn(void);
    static bool m_isRunning;
    static SDL_Event m_event;
    static bool turn;
    static Piece* draggingPiece;
};
