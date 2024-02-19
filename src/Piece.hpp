#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Piece {
  public:
    Piece(std::string texturePath,bool color);
    ~Piece();
    void spawn(int x, int y);

  protected:
    bool m_isAlive;
    bool m_color;
    int m_xPos;
    int m_yPos;
    std::string m_texturePath;
    SDL_Texture* m_texture;
    SDL_Rect m_srcRect;

  private:

};
