#include <iostream>
#include <map>

#include "Game.hpp"
#include "const.hpp"
#include "Piece.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

SDL_Window *Game::m_window = NULL;
SDL_Renderer *Game::renderer = NULL;
SDL_Event Game::m_event;
bool Game::m_isRunning = false;
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
  static int offsetX, offsetY;
  static int oldX, oldY;
  static int XPos, YPos;
  static bool isDragging = false;
  static Piece *piece = nullptr;
  SDL_WaitEvent(&m_event);
  switch (m_event.type) {
  case SDL_QUIT:
    m_isRunning = false;
    break;
  case SDL_MOUSEBUTTONDOWN :
    if (m_event.button.button == SDL_BUTTON_LEFT) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        piece = board[{mouseX/SQUARE_SIZE, mouseY/SQUARE_SIZE}];
        if (piece) {
          XPos = mouseX;
          YPos = mouseY;
          oldX = XPos/SQUARE_SIZE;
          oldY = YPos/SQUARE_SIZE;
          std::cout << "here" << std::endl;
          std::cout << "XPos: " << XPos << " YPos: " << YPos << std::endl;
          std::cout << "mouseX: " << mouseX << " mouseY: " << mouseY << std::endl;
          std::cout << "pieceX: " << piece->getX() << " pieceY: " << piece->getY() << std::endl;
          isDragging = true;
          std::cout << "isDragging" << std::endl;
        }
    }
    break;
  case SDL_MOUSEBUTTONUP :
    if (m_event.button.button == SDL_BUTTON_LEFT) {
        isDragging = false;
        if (piece) {
          XPos /= SQUARE_SIZE;
          YPos /= SQUARE_SIZE;
          std::cout << "XPos: " << XPos << " YPos: " << YPos << std::endl;
          piece->setX(XPos);
          piece->setY(YPos);
          board[{oldX, oldY}] = nullptr;
          std::cout << "mouse up" << std::endl;
        }
    }
    break;
  case SDL_MOUSEMOTION :
    if (isDragging) {
      SDL_GetMouseState(&XPos, &YPos);
      //piece->freeSpawn(XPos, YPos);
      //piece->setX(XPos);
      //piece->setY(YPos);
      std::cout << "mouse motion" << std::endl;
    }
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
