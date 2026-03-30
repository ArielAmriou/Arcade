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
    ../../include/Shared/
)

add_library(${SDL2} SHARED ${SRCS_SDL2})
target_include_directories(${SDL2} PRIVATE ${SHARED} ${SDL2}/include/)
target_link_libraries(${SDL2} SDL2 SDL2_image SDL2_mixer)

add_custom_target(move ALL
    DEPENDS ${SDL2}
    COMMAND mv lib*.so ../
)
