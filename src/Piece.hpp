#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Piece {
  public:
    Piece(bool color);
    ~Piece();
    void spawn(void);
    int getX(void);
    int getY(void);
    void setX(int x);
    void setY(int y);

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
