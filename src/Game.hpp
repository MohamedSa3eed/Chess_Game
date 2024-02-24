#pragma once

#include <SDL2/SDL.h>
#include <map>

#include "Piece.hpp"

class Game
{
  public: 
    static SDL_Renderer* renderer;
    static std::map<std::pair<int, int>, Piece*> board;

    static Game& getInstance(void);
    static void render(void);
    static void handleEvents(void);
    static void update(void);
    static bool isRunning(void);
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

  private:
    static bool m_isRunning;
    static SDL_Window* m_window;
    static SDL_Event m_event;

    Game(void);
    ~Game(void);
    int init(void);
    static void drawChessBoard(void);
};
