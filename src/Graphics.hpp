#pragma once 
#include <SDL2/SDL.h>
#include "Piece.hpp"

class Graphics {
  public: 
    static void drawPiece(const Piece &piece);
    static void drawChessBoard(void);
    static void clear(void);
    static void present(void);
    static SDL_Texture* getTexture(const Piece &piece);
    static bool init(void);
    static void cleanup(void);
    static Graphics& getInstance(void);
    Graphics(Graphics const&) = delete;
    void operator=(Graphics const&) = delete;

  private:

    static SDL_Renderer* renderer;
    static SDL_Window* window;

    Graphics(void);
    ~Graphics(void);
};
