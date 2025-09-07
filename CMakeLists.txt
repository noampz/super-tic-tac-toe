cmake_minimum_required(VERSION 3.20)
project(TIC-TAC-TOE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADERS
    ./src/board.hpp
    ./src/game.hpp
    ./src/data_structure/treeNode.hpp
    ./src/solver.hpp
)

set(SOURCES
    ./src/board.cpp
    ./src/game.cpp
    app.cpp
    ./src/solver.cpp
)

add_executable(tic_tac_toe ${SOURCES} ${HEADERS})