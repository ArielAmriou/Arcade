cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SNAKE
    arcade_snake
)

set(SRCS_SNAKE
    ${SNAKE}/src/Game.cpp
)

set(SHARED
    ../../include/Shared/
)

add_library(${SNAKE} SHARED ${SRCS_SNAKE})
target_include_directories(${SNAKE} PRIVATE ${SHARED} ${SNAKE}/include/)

add_custom_target(move ALL
    DEPENDS ${SNAKE}
    COMMAND mv lib*.so ../
)
