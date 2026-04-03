cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/Core.cpp
    src/DLLoader.cpp
)

set(HEADERS
    include/
    include/Shared
)

add_executable(arcade ${MAIN} ${SRCS})
target_include_directories(arcade PRIVATE ${HEADERS})

target_compile_options(arcade PRIVATE)

add_custom_target(core
    DEPENDS arcade
)

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
    tests/tests_base.cpp
)

add_executable(tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS})
target_include_directories(tests_run_bin PRIVATE ${HEADERS})
target_compile_options(tests_run_bin PRIVATE --coverage)
target_link_libraries(tests_run_bin criterion --coverage)

add_custom_target(tests_run
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.gcda
    COMMAND ${CMAKE_COMMAND} -E rm -f log.bin
    COMMAND ./tests_run_bin
    COMMAND ${CMAKE_COMMAND} -E rm -f log.bin rom.bin
    DEPENDS tests_run_bin
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(graphicals ALL
    COMMAND ${CMAKE_COMMAND} -B../lib/graphicals -S../lib/graphicals
    COMMAND make -C ../lib/graphicals
)

add_custom_target(games ALL
    COMMAND ${CMAKE_COMMAND} -B../lib/games -S../lib/games
    COMMAND make -C ../lib/games
)
