# Dancing Sudoku

This solver treats sudoku as an [exact cover](https://en.wikipedia.org/wiki/Exact_cover) problem and solves it efficiently using [dancing links](https://en.wikipedia.org/wiki/Dancing_Links).
One of the main benefit of this technique is that it does not require a single copy when doing backtracking.
What's more, the solver uses a min-heap structure to prioritize branches with fewest possibilities during exploration.
This approach combined with early pruning of impossible cases allow us to considerably reduce the number of cases to explore, sometimes requiring no backtracking at all.

## Usage

To build the solver, make sure that you have `cmake` installed on your machine and then run `cmake . && make`.

The solver reads a sudoku grid from the standard input and prints the solution to standard output.

You can specify the grid size by passing it as the first argument (for instance `solver 16`), by default it is equal to 9.

With grid size set to `n`, the input grid is expected to have `n` lines of `n` numbers separated by space, with empty cells represented as `0`.
For instance:
```
0 6 0 0 5 0 0 0 0
0 0 0 0 0 0 8 4 0
0 5 3 0 0 0 0 0 0
1 0 0 9 0 0 0 0 6
0 0 6 3 0 8 0 0 7
8 0 0 6 0 0 0 0 4
0 7 1 0 0 0 0 0 0
0 0 0 0 0 0 3 9 0
0 8 0 0 4 0 0 0 0
```

The repository contains some example grids in the `examples` folder.
You can test them with `./solver < examples/whatever_grid_you_want.txt`

## References

If you want to learn more about dancing links and exact cover, have a look at [Donald Knuth's paper](https://arxiv.org/abs/cs/0011047).

[This article](http://mathieuturcotte.ca/textes/couverture-exacte-sudoku/) (in French) written by Mathieu Turcotte gives an interesting explanation on how to see sudoku as an exact cover problem.
