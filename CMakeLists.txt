cmake_minimum_required(VERSION 3.20)
project(TIC-TAC-TOE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADERS
    board.hpp
    game.hpp
)

set(SOURCES
    board.cpp
    game.cpp
    app.cpp

)

add_executable(tic_tac_toe ${SOURCES} ${HEADERS})