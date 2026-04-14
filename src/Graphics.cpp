#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Piece.hpp"
#include "const.hpp"
#include "Graphics.hpp"

SDL_Renderer* Graphics::renderer = nullptr;
SDL_Window* Graphics::window = nullptr;

SDL_Texture* Graphics::getTexture(const Piece &piece) {

  SDL_Texture* texture = IMG_LoadTexture(renderer, piece.texturePath.c_str());
  if (!texture) {
      std::cerr << "Failed to load texture: " << piece.texturePath << std::endl;
      return nullptr;
  }
  return texture;
}

void Graphics::drawChessBoard(void) {
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

void Graphics::drawPiece(const Piece &piece) {
  SDL_RenderCopy(renderer, piece.texture, NULL, &piece.body);
}

void Graphics::clear(void) {
  SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
  SDL_RenderClear(renderer);
}

void Graphics::present(void) {
  SDL_RenderPresent(renderer);
}

bool Graphics::init(void) { 

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "SDL init error" << std::endl;
      return false;
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
      std::cerr << "IMG init error" << std::endl;
      return false;
  }

  window = SDL_CreateWindow("Chess Game",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window creation error" << std::endl; 
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer creation error" << std::endl; 
    return false;
  }

  return true;
}

void Graphics::cleanup(void) {
  if (renderer) SDL_DestroyRenderer(renderer);
  if (window) SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
