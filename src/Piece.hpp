#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Piece {
  public:

    Piece(bool color);
    ~Piece();
    void spawn(int x, int y);
    //virtual  void move(int x, int y) = 0;
    bool getColor(void);
    std::string texturePath;
    SDL_Texture* texture;
    SDL_Rect body;

  protected:
    bool m_isAlive;
    bool m_color;
    int m_xPos;
    int m_yPos;

    //virtual bool isLegalMove(int x, int y) = 0;

  private:

};

class King : public Piece {
  public:
    King(bool color);
    ~King();

  private:

};

class Queen : public Piece {
  public:
    Queen(bool color);
    ~Queen();

  private:

};

class Knight : public Piece {
public:
    Knight(bool color, int position);
    ~Knight();

  private:

};

class Bishop : public Piece {
  public:
    Bishop(bool color, int position);
    ~Bishop();

  private:

};

class Rook : public Piece {
  public:
    Rook(bool color, int position);
    ~Rook();

  private:

};

class Pawn : public Piece {
  public:
    Pawn(bool color, int id);
    ~Pawn();

  private:

};
