#ifndef SDL_HANDLER_HPP
#define SDL_HANDLER_HPP

#include <SDL2/SDL.h>

class SDL_handler
{
  public: 
    SDL_Event event;

    static SDL_handler& getInstance(void);
    static void renderChessBoard(void);
    SDL_handler(SDL_handler const&) = delete;
    void operator=(SDL_handler const&) = delete;

  private:
    static SDL_Window* m_window;
    static SDL_Renderer* m_renderer;

    SDL_handler(void);
    ~SDL_handler(void);
    int init(void);
    static void drawChessBoard(void);
};

#endif
