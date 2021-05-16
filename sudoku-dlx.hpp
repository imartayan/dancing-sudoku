#ifndef SUDOKU_DLX_HPP
#define SUDOKU_DLX_HPP

#include "dlx.hpp"
#include <vector>

namespace sudoku {

std::vector<Column *> make_cols(int size);
std::vector<Line *> make_lines(int size, std::vector<Column *> &cols);

} // namespace sudoku

#endif // SUDOKU_DLX_HPP
