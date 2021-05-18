#include "sudoku.hpp"
#include <iostream>

int main(int argc, char **argv) {
  const int size = argc > 1 ? atoi(argv[1]) : 9;

  auto cols = sudoku::make_cols(size);
  auto lines = sudoku::make_lines(size, cols);
  auto problem = ExactCover(cols, lines);
  sudoku::parse(problem, size);

  if (!problem.solve()) {
    std::cerr << "No solution" << std::endl;
    return 1;
  }
  sudoku::print(problem, size);

  for (auto line : lines)
    delete line;
  for (auto col : cols)
    delete col;
  return 0;
}
