#include "dlx.hpp"

Cell *Cell::get_next() const { return next; }
Line *Cell::get_line() const { return line; }
Column *Cell::get_col() const { return col; }

void Cell::remove() const {
  previous->next = next;
  next->previous = previous;
}

void Cell::restore() {
  previous->next = this;
  next->previous = this;
}

void Cell::append(Cell *other) {
  other->previous = this;
  other->next = next;
  next->previous = other;
  next = other;
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

std::vector<std::vector<Line *>> Line::select() {
  std::vector<std::vector<Line *>> stacks;
  if (state == 0) {
    state = 1;
    for (auto cell : cells)
      stacks.push_back(cell->get_col()->remove());
  }
  return stacks;
}

void Line::unselect(std::vector<std::vector<Line *>> &stacks) {
  if (state == 1) {
    state = 0;
    for (int i = stacks.size() - 1; i >= 0; i--)
      cells[i]->get_col()->restore(stacks[i]);
  }
}

void Line::remove() {
  if (state == 0) {
    state = -1;
    for (auto cell : cells) {
      cell->remove();
      auto col = cell->get_col();
      col->size--;
      if (col->heap != nullptr)
        col->heap->decrease(col, col->size);
    }
  }
}

void Line::restore() {
  if (state == -1) {
    state = 0;
    for (int i = cells.size() - 1; i >= 0; i--) {
      cells[i]->restore();
      auto col = cells[i]->get_col();
      col->size++;
      if (col->heap != nullptr)
        col->heap->increase(col, col->size);
    }
  }
}

Column::Column() : head(new Cell(nullptr, this)) {}
Column::~Column() { delete head; }

int Column::get_size() const { return size; }
Cell *Column::get_head() const { return head; }

std::vector<Line *> Column::remove() {
  if (heap != nullptr)
    heap->remove(this);
  std::vector<Line *> stack;
  Cell *cell = head->get_next();
  while (cell != head) {
    auto line = cell->get_line();
    if (line->state == 0) {
      line->remove();
      stack.push_back(line);
    }
    cell = cell->get_next();
  }
  return stack;
}

void Column::restore(std::vector<Line *> &stack) {
  while (!stack.empty()) {
    auto line = stack.back();
    line->restore();
    stack.pop_back();
  }
  if (heap != nullptr)
    heap->restore(this);
}
