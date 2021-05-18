#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include "dlx.hpp"
#include <vector>

namespace sudoku {

std::vector<Column *> make_cols(int size);
std::vector<Line *> make_lines(int size, std::vector<Column *> &cols);

void parse(ExactCover &problem, int size);
void print(ExactCover &problem, int size);

} // namespace sudoku

#endif // SUDOKU_HPP
