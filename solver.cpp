#include "heap.hpp"
#include "sudoku-dlx.hpp"
#include "utils.hpp"

bool solve(Heap<Column *, int> *heap) {
  if (heap->is_empty())
    return true;
  auto col = heap->take_min();
  int n = col->get_size();
  if (n == 0)
    return false;
  auto head = col->get_head();
  auto cell = head->get_next();
  while (cell != head) {
    auto line = cell->get_line();
    auto stacks = line->select();
    if (solve(heap))
      return true;
    line->unselect(stacks);
    cell = cell->get_next();
  }
  return false;
}

int main(int argc, char **argv) {
  int size = 9;
  if (argc > 1)
    size = atoi(argv[1]);

  auto heap = new Heap<Column *, int>;
  auto cols = make_cols(size, heap);
  auto lines = make_lines(size, cols);
  for (auto col : cols)
    heap->append(col, col->get_size());
  heap->heapify();

  auto grid = parse_grid(size);
  for (int i = 0; i < size * size; i++) {
    int k = grid[i];
    if (k > 0)
      lines[i * size + k - 1]->select();
  }

  if (!solve(heap)) {
    std::cerr << "No solution" << std::endl;
    return 1;
  }

  for (int i = 0; i < size * size; i++)
    for (int k = 0; k < size; k++) {
      auto line = lines[i * size + k];
      if (line->is_selected())
        grid[i] = k + 1;
    }
  print_grid(size, grid);

  for (auto line : lines)
    delete line;
  for (auto col : cols)
    delete col;
  delete heap;
  return 0;
}
