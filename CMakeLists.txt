cmake_minimum_required(VERSION 3.2)

project(Chess)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SDL2)
