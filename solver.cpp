#include "sudoku-dlx.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
  int size = 9;
  if (argc > 1)
    size = atoi(argv[1]);

  auto cols = sudoku::make_cols(size);
  auto lines = sudoku::make_lines(size, cols);
  auto problem = ExactCover(cols, lines);
  auto grid = parse_grid(size);
  for (int i = 0; i < size * size; i++) {
    int k = grid[i];
    if (k > 0)
      problem.select(i * size + k - 1);
  }

  if (!problem.solve()) {
    std::cerr << "No solution" << std::endl;
    return 1;
  }

  for (int i = 0; i < size * size; i++)
    for (int k = 0; k < size; k++)
      if (problem.is_selected(i * size + k))
        grid[i] = k + 1;
  print_grid(size, grid);

  for (auto line : lines)
    delete line;
  for (auto col : cols)
    delete col;
  return 0;
}
