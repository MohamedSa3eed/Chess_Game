cmake_minimum_required(VERSION 3.2)

project(Chess)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(src)

set(SOURCE_FILES src/main.cpp
                 src/Game.cpp
                 src/Piece.cpp
                 src/King.cpp
  )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)
