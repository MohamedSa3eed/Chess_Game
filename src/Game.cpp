#include "Game.hpp"
#include "const.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

SDL_Window *Game::m_window = NULL;
SDL_Renderer *Game::renderer = NULL;
SDL_Event Game::m_event;
bool Game::m_isRunning = false;

Game &Game::getInstance() {
  static Game instance;
  return instance;
}

Game::Game() {
  m_window = NULL;
  renderer = NULL;
  m_isRunning = false;
  init();
}

Game::~Game() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

int Game::init() {
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
    }
    else {
      renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
      if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        ret = 1;
      }
      else {
        m_isRunning = true;
      }
    }
  }
  return ret;
}

void Game::drawChessBoard() {

  bool isLight = true;
  SDL_Rect square;

  for (int i = 0; i < CHESSBOARD_SIZE; ++i) {
    for (int j = 0; j < CHESSBOARD_SIZE; ++j) {
      square.x = j * SQUARE_SIZE;
      square.y = i * SQUARE_SIZE;
      square.w = SQUARE_SIZE;
      square.h = SQUARE_SIZE;

      SDL_SetRenderDrawColor(renderer, isLight ? lightColor.r : darkColor.r,
                             isLight ? lightColor.g : darkColor.g,
                             isLight ? lightColor.b : darkColor.b,
                             isLight ? lightColor.a : darkColor.a);

      SDL_RenderFillRect(renderer, &square);
      isLight = !isLight;
    }
    isLight = !isLight;
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  Game::getInstance().drawChessBoard();
}

void Game::handleEvents() {
  SDL_WaitEvent(&m_event);
  switch (m_event.type) {
  case SDL_QUIT:
    m_isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update() {
  SDL_RenderPresent(renderer);
}

bool Game::isRunning() { 
  return Game::getInstance().m_isRunning;
}
