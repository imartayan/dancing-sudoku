cmake_minimum_required(VERSION 3.0)

project(dancing-sudoku)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wreturn-type -Werror=return-type -Wunreachable-code")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver
    solver.cpp
    heap.hpp
    dlx.cpp dlx.hpp
    sudoku-dlx.cpp sudoku-dlx.hpp
)
