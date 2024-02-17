#include "const.hpp"
#include "SDL_handler.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

SDL_Window* SDL_handler::m_window = NULL;
SDL_Renderer* SDL_handler::m_renderer = NULL;

SDL_handler& SDL_handler::getInstance() {
  static SDL_handler instance;
  return instance;
}

SDL_handler::SDL_handler() {
  m_window = NULL;
  m_renderer = NULL;
  init();
}

SDL_handler::~SDL_handler() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

int SDL_handler::init() {
  int ret = 0;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL initialization failed: %s",
                 SDL_GetError());
    ret = 1;
  } else {
    m_window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HIGHT, SDL_WINDOW_SHOWN);
    if (!m_window) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation failed: %s",
                   SDL_GetError());
      SDL_Quit();
      ret = 1;
    } else {
      m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
      if (!m_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        ret = 1;
      }
    }
  }
  return ret;
}

void SDL_handler::drawChessBoard() {

  bool isLight = true;
  SDL_Rect square;

  for (int i = 0; i < CHESSBOARD_SIZE; ++i) {
    for (int j = 0; j < CHESSBOARD_SIZE; ++j) {
      square.x = j * SQUARE_SIZE;
      square.y = i * SQUARE_SIZE;
      square.w = SQUARE_SIZE;
      square.h = SQUARE_SIZE;

      SDL_SetRenderDrawColor(m_renderer, isLight ? lightColor.r : darkColor.r,
                             isLight ? lightColor.g : darkColor.g,
                             isLight ? lightColor.b : darkColor.b,
                             isLight ? lightColor.a : darkColor.a);

      SDL_RenderFillRect(m_renderer, &square);
      isLight = !isLight;
    }
    isLight = !isLight;
  }
}

void SDL_handler::renderChessBoard() {
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  SDL_RenderClear(m_renderer);
  drawChessBoard();
  SDL_RenderPresent(m_renderer);
}
