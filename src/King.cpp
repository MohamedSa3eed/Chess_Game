#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Piece.hpp"
#include "King.hpp"

King::King(std::string texturePath, bool color)
    : Piece(texturePath, color) {

}

King::~King() {

}
