#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Piece {
  public:

    std::string texturePath;
    SDL_Texture* texture;
    SDL_Rect body;

    Piece() = default;
    Piece(bool color);
    virtual ~Piece();

    void spawn(int x, int y);
    void move(int x, int y);
    virtual bool isValidMove(int x, int y) = 0;
    bool getColor(void);

  protected:
    bool m_isAlive;
    bool m_color;
    int m_xPos;
    int m_yPos;
    bool m_hasMoved = false;

  private:

  public:
    bool hasMoved(void);
    void setHasMoved(bool moved);

};

class King : public Piece {
  public:
    King(bool color);
    ~King() = default;

    bool isValidMove(int x, int y) override;

  private:

};

class Queen : public Piece {
  public:
    Queen(bool color);
    ~Queen() = default;

    bool isValidMove(int x, int y) override;

  private:

};

class Knight : public Piece {
public:
    Knight(bool color, int position);
    ~Knight() = default;

    bool isValidMove(int x, int y) override;

  private:

};

class Bishop : public Piece {
  public:
    Bishop(bool color, int position);
    ~Bishop() = default;

    bool isValidMove(int x, int y) override;

  private:

};

class Rook : public Piece {
  public:
    Rook(bool color, int position);
    ~Rook() = default;

    bool isValidMove(int x, int y) override;

  private:

};

class Pawn : public Piece {
  public:
    Pawn(bool color, int id);
    ~Pawn() = default;

    bool isValidMove(int x, int y) override;

  private:

};
