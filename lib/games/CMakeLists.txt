cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_SHARED
    ../../include/Shared/
    shared/include/
    ../../include/
)

set(SRCS_SHARED
    ../../src/DLLoader.cpp
    ../../src/Utils.cpp
)

set(SNAKE
    arcade_snake
)

set(SRCS_SNAKE
    ${SNAKE}/src/GameSnake.cpp
)

add_library(${SNAKE} SHARED ${SRCS_SNAKE} ${SRCS_SHARED})
target_include_directories(${SNAKE} PRIVATE ${INCLUDE_SHARED} ${SNAKE}/include/)
set_target_properties(${SNAKE} PROPERTIES PREFIX "")

set(MENU
    arcade_menu
)

set(SRCS_MENU
    ${MENU}/src/GameMenu.cpp
    ${MENU}/src/Score.cpp
)

add_library(${MENU} SHARED ${SRCS_MENU} ${SRCS_SHARED})
target_include_directories(${MENU} PRIVATE ${INCLUDE_SHARED} ${MENU}/include/)
set_target_properties(${MENU} PROPERTIES PREFIX "")

add_custom_target(move ALL
    DEPENDS ${SNAKE} ${MENU}
    COMMAND mv *.so ../
)
