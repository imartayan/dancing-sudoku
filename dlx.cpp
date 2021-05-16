#include "dlx.hpp"

Cell::Cell(Line *l, Column *c) : previous(this), next(this), line(l), col(c) {}

Cell *Cell::get_next() const { return next; }
Line *Cell::get_line() const { return line; }
Column *Cell::get_col() const { return col; }

void Cell::append(Cell *other) {
  other->previous = this;
  other->next = next;
  next->previous = other;
  next = other;
}

void Cell::remove() const {
  previous->next = next;
  next->previous = previous;
}

void Cell::restore() {
  previous->next = this;
  next->previous = this;
}

Line::Line(std::vector<Column *> &selected_cols) {
  for (auto col : selected_cols) {
    auto cell = new Cell(this, col);
    cells.push_back(cell);
    col->head->append(cell);
    col->size++;
  }
}

Line::~Line() {
  for (auto cell : cells)
    delete cell;
}

bool Line::is_selected() const { return state == 1; }

std::vector<std::vector<Line *>> Line::select(Heap<Column *, int> *heap) {
  std::vector<std::vector<Line *>> stacks;
  if (state == 0) {
    state = 1;
    for (auto cell : cells)
      stacks.push_back(cell->get_col()->remove(heap));
  }
  return stacks;
}

void Line::unselect(std::vector<std::vector<Line *>> &stacks,
                    Heap<Column *, int> *heap) {
  if (state == 1) {
    state = 0;
    for (int i = stacks.size() - 1; i >= 0; i--)
      cells[i]->get_col()->restore(stacks[i], heap);
  }
}

void Line::remove(Heap<Column *, int> *heap) {
  if (state == 0) {
    state = -1;
    for (auto cell : cells) {
      cell->remove();
      auto col = cell->get_col();
      col->size--;
      if (heap != nullptr)
        heap->decrease(col, col->size);
    }
  }
}

void Line::restore(Heap<Column *, int> *heap) {
  if (state == -1) {
    state = 0;
    for (int i = cells.size() - 1; i >= 0; i--) {
      cells[i]->restore();
      auto col = cells[i]->get_col();
      col->size++;
      if (heap != nullptr)
        heap->increase(col, col->size);
    }
  }
}

Column::Column() : head(new Cell(nullptr, this)) {}
Column::~Column() { delete head; }

int Column::get_size() const { return size; }
Cell *Column::get_head() const { return head; }

std::vector<Line *> Column::remove(Heap<Column *, int> *heap) {
  if (heap != nullptr)
    heap->remove(this);
  std::vector<Line *> stack;
  Cell *cell = head->get_next();
  while (cell != head) {
    auto line = cell->get_line();
    if (line->state == 0) {
      line->remove(heap);
      stack.push_back(line);
    }
    cell = cell->get_next();
  }
  return stack;
}

void Column::restore(std::vector<Line *> &stack, Heap<Column *, int> *heap) {
  while (!stack.empty()) {
    auto line = stack.back();
    line->restore(heap);
    stack.pop_back();
  }
  if (heap != nullptr)
    heap->restore(this);
}

ExactCover::ExactCover(std::vector<Column *> &c, std::vector<Line *> &l)
    : cols(c), lines(l) {
  for (auto col : cols)
    heap.append(col, col->get_size());
  heap.heapify();
}

bool ExactCover::is_selected(int i) const { return lines[i]->is_selected(); }

void ExactCover::select(int i) { lines[i]->select(&heap); }

bool ExactCover::solve() {
  if (heap.is_empty())
    return true;
  auto col = heap.take_min();
  int n = col->get_size();
  if (n == 0)
    return false;
  auto head = col->get_head();
  auto cell = head->get_next();
  while (cell != head) {
    auto line = cell->get_line();
    auto stacks = line->select(&heap);
    if (solve())
      return true;
    line->unselect(stacks, &heap);
    cell = cell->get_next();
  }
  return false;
}
