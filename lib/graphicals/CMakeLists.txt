cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2
    arcade_sdl2
)

set(SRCS_SDL2
    ${SDL2}/src/DisplaySDL2.cpp
)

set(SHARED
    ../../include/Shared/
)

add_library(${SDL2} SHARED ${SRCS_SDL2})
target_include_directories(${SDL2} PRIVATE ${SHARED} ${SDL2}/include/)
target_link_libraries(${SDL2} SDL2 SDL2_image SDL2_mixer SDL2_ttf)
set_target_properties(${SDL2} PROPERTIES PREFIX "")

set(NCURSES
        arcade_ncurses
)

set(SRCS_NCURSES
        ${NCURSES}/src/DisplayNcurses.cpp
        arcade_ncurses/src/DisplayNcurses.cpp
)

set(SHARED
        ../../include/Shared/
)

add_library(${NCURSES} SHARED ${SRCS_NCURSES})

target_include_directories(${NCURSES} PRIVATE ${SHARED} ${NCURSES}/include/)
target_link_libraries(${NCURSES} ncurses)
set_target_properties(${NCURSES} PROPERTIES PREFIX "")

set(SFML
    arcade_sfml
)

set(SRCS_SFML
    ${SFML}/src/DisplaySFML.cpp
)

add_library(${SFML} SHARED ${SRCS_SFML})
target_include_directories(${SFML} PRIVATE ${SHARED} ${SFML}/include/)
target_link_libraries(${SFML} sfml-graphics sfml-window sfml-system sfml-audio)
set_target_properties(${SFML} PROPERTIES PREFIX "")

add_custom_target(move ALL
    DEPENDS ${SDL2} ${NCURSES} ${SFML}
    COMMAND mv *.so ../
)

