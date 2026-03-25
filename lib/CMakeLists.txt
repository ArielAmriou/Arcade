cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2
    arcade_sdl2
)

set(SRCS_SDL2
    ${SDL2}/src/Display.cpp
)

set(SHARED
    ../include/
)

add_library(${SDL2} SHARED ${SRCS_SDL2})
target_include_directories(${SDL2} PRIVATE ${SHARED} ${SDL2}/include/)

set(SNAKE
    arcade_snake
)

set(SRCS_SNAKE
    ${SNAKE}/src/Game.cpp
)

set(SHARED
    ../include/
)

add_library(${SNAKE} SHARED ${SRCS_SNAKE})
target_include_directories(${SNAKE} PRIVATE ${SHARED} ${SNAKE}/include/)

