#ifndef CONST_HPP
#define CONST_HPP

#include <array>
#include <string>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 480;
const int WINDOW_HIGHT = 480;
const int CHESSBOARD_SIZE = 8;
const int SQUARE_SIZE = WINDOW_WIDTH / CHESSBOARD_SIZE;
const int PIECE_SIZE = SQUARE_SIZE;
const SDL_Color lightColor = {240, 240, 220, 255};
const SDL_Color darkColor = {139, 69, 19, 255};

// Assets Paths
const std::string ASSETS_PATH = "../assets/";
const std::string WHITE_PAWN = ASSETS_PATH + "Chess_wpawn.png";
const std::string BLACK_PAWN = ASSETS_PATH + "Chess_bpawn.png";
const std::string WHITE_KNIGHT = ASSETS_PATH + "Chess_wknight.png";
const std::string BLACK_KNIGHT = ASSETS_PATH + "Chess_bknight.png";
const std::string WHITE_BISHOP = ASSETS_PATH + "Chess_wbishop.png";
const std::string BLACK_BISHOP = ASSETS_PATH + "Chess_bbishop.png";
const std::string WHITE_ROOK = ASSETS_PATH + "Chess_wrook.png";
const std::string BLACK_ROOK = ASSETS_PATH + "Chess_brook.png";
const std::string WHITE_QUEEN = ASSETS_PATH + "Chess_wqueen.png";
const std::string BLACK_QUEEN = ASSETS_PATH + "Chess_bqueen.png";
const std::string WHITE_KING = ASSETS_PATH + "Chess_wking.png";
const std::string BLACK_KING = ASSETS_PATH + "Chess_bking.png";

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


// Default positions
const std::array<std::pair<int, int>,CHESSBOARD_SIZE> WHITE_PAWN_POSITIONS = {
  { {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6} }  
};
const std::array<std::pair<int, int>,CHESSBOARD_SIZE> BLACK_PAWN_POSITIONS = {
  { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1} }
};
const std::pair<int, int> WHITE_KING_POSITION = {4, 7};
const std::pair<int, int> BLACK_KING_POSITION = {4, 0};
const std::pair<int, int> WHITE_QUEEN_POSITION = {3, 7};
const std::pair<int, int> BLACK_QUEEN_POSITION = {3, 0};
const std::pair<int, int> WHITE_LEFT_BISHOP_POSITION = {2, 7};
const std::pair<int, int> WHITE_RIGHT_BISHOP_POSITION = {5, 7};
const std::pair<int, int> BLACK_LEFT_BISHOP_POSITION = {2, 0};
const std::pair<int, int> BLACK_RIGHT_BISHOP_POSITION = {5, 0};
const std::pair<int, int> WHITE_LEFT_KNIGHT_POSITION = {1, 7};
const std::pair<int, int> WHITE_RIGHT_KNIGHT_POSITION = {6, 7};
const std::pair<int, int> BLACK_LEFT_KNIGHT_POSITION = {1, 0};
const std::pair<int, int> BLACK_RIGHT_KNIGHT_POSITION = {6, 0};
const std::pair<int, int> WHITE_LEFT_ROOK_POSITION = {0, 7};
const std::pair<int, int> WHITE_RIGHT_ROOK_POSITION = {7, 7};
const std::pair<int, int> BLACK_LEFT_ROOK_POSITION = {0, 0};
const std::pair<int, int> BLACK_RIGHT_ROOK_POSITION = {7, 0};

const bool WHITE = true;
const bool BLACK = false;
const int RIGHT = 1;
const int LEFT = 2;

#endif
