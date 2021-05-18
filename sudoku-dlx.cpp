#include "sudoku-dlx.hpp"
#include <cmath>
#include <iostream>

namespace sudoku {

std::vector<Column *> make_cols(int size) {
  std::vector<Column *> cols;
  for (int i = 0; i < size * size * 4; i++)
    cols.push_back(new Column());
  return cols;
}

std::vector<Line *> make_lines(int size, std::vector<Column *> &cols) {
  int sqrt = std::floor(std::sqrt(size));
  std::vector<Line *> lines;
  std::vector<Column *> selected_cols(4);
  int block;
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
      selected_cols[0] = cols[i * size + j];
      block = (i / sqrt) * sqrt + (j / sqrt);
      for (int k = 0; k < size; k++) {
        selected_cols[1] = cols[i * size + k + size * size];
        selected_cols[2] = cols[j * size + k + size * size * 2];
        selected_cols[3] = cols[block * size + k + size * size * 3];
        lines.push_back(new Line(selected_cols));
      }
    }
  return lines;
}

void parse(ExactCover &problem, int size) {
  int k;
  for (int i = 0; i < size * size; i++) {
    std::cin >> k;
    if (1 <= k && k <= size)
      problem.select(i * size + k - 1);
  }
}

void print(ExactCover &problem, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        if (problem.is_selected((i * size + j) * size + k)) {
          std::cout << k + 1;
          break;
        }
      }
      if (j < size - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}

} // namespace sudoku
