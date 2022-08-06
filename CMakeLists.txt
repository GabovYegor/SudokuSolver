cmake_minimum_required(VERSION 3.22)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
    Board.h
    SudokuSolver.h
    )

set(SOURCE_FILES
    Board.cpp
    SudokuSolver.cpp
    )

add_library(SudokuSolver ${HEADER_FILES} ${SOURCE_FILES})
add_subdirectory(tests)
