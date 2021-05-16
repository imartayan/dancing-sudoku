#ifndef DLX_HPP
#define DLX_HPP

#include "heap.hpp"
#include <vector>

class Line;
class Column;

class Cell {
private:
  Cell *previous;
  Cell *next;
  Line *const line;
  Column *const col;

public:
  Cell(Line *l, Column *c) : previous(this), next(this), line(l), col(c) {}

  Cell *get_next() const;
  Line *get_line() const;
  Column *get_col() const;

  void remove() const;
  void restore();
  void append(Cell *other);
};

class Line {
private:
  friend Column;
  int state = 0;
  std::vector<Cell *> cells;

public:
  Line(std::vector<Column *> &selected_cols);
  ~Line();

  bool is_selected() const;
  std::vector<std::vector<Line *>> select();
  void unselect(std::vector<std::vector<Line *>> &stacks);
  void remove();
  void restore();
};

class Column {
private:
  friend Line;
  int size = 0;
  Cell *const head;

public:
  static Heap<Column *, int> *const heap;

  Column();
  ~Column();

  int get_size() const;
  Cell *get_head() const;

  std::vector<Line *> remove();
  void restore(std::vector<Line *> &stack);
};

#endif // DLX_HPP
