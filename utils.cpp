#include "utils.hpp"

std::vector<int> parse_grid(int size) {
  std::vector<int> grid;
  int k;
  for (int i = 0; i < size * size; i++) {
    std::cin >> k;
    grid.push_back(k);
  }
  return grid;
}

void print_grid(int size, std::vector<int> &grid) {
  for (int i = 0; i < size * size; i += size) {
    for (int j = i; j < i + size; j++) {
      std::cout << grid[j];
      if (j < i + size - 1)
        std::cout << ' ';
    }
    std::cout << std::endl;
  }
}
