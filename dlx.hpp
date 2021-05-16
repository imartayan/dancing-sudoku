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
  Cell(Line *l, Column *c);

  Cell *get_next() const;
  Line *get_line() const;
  Column *get_col() const;

  void append(Cell *other);
  void remove() const;
  void restore();
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
  std::vector<std::vector<Line *>> select(Heap<Column *, int> *heap);
  void unselect(std::vector<std::vector<Line *>> &stacks,
                Heap<Column *, int> *heap);

  void remove(Heap<Column *, int> *heap);
  void restore(Heap<Column *, int> *heap);
};

class Column {
private:
  friend Line;
  int size = 0;
  Cell *const head;

public:
  Column();
  ~Column();

  int get_size() const;
  Cell *get_head() const;

  std::vector<Line *> remove(Heap<Column *, int> *heap);
  void restore(std::vector<Line *> &stack, Heap<Column *, int> *heap);
};

class ExactCover {
private:
  const std::vector<Column *> cols;
  const std::vector<Line *> lines;
  Heap<Column *, int> heap;

public:
  ExactCover(std::vector<Column *> &c, std::vector<Line *> &l);

  bool is_selected(int i) const;
  void select(int i);
  bool solve();
};

#endif // DLX_HPP
