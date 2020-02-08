#include "../src/sudoku.h"

void test_square_constructor0()
{
  Square *sq = new Square();
  assert(!sq->certain && sq->possible_values.size() == 0 && "test_square_constructor0: default constructor failed");
}

void test_square_constructor1()
{
  dataype val = 1;
  Square *sq = new Square(val);
  assert(sq->certain && sq->possible_values.size() == 1 && sq->possible_values.count(val) && "test_square_constructor1: integer constructor failed");
}

void test_square_constructor2()
{
  dataype val = 1;
  unordered_set<dataype> vals({1,2});
  Square *sq = new Square(vals);
  assert(!sq->certain && sq->possible_values.size() == 2 && "test_square_constructor2: set constructor failed");
}

void test_board_constructor0()
{
  size_t board_size = 9;
  Board *board = new Board(board_size);
  assert(board && board->dimension == board_size && board->grid.size() == board->dimension && board->grid[0].size() == board->dimension && "test_board_constructor0: board constructor failed");
}

void test_board_constructor1()
{
  // construct grid
  size_t dimension = 9;
  vector<vector<Square>> grid = vector<vector<Square>>(dimension, vector<Square>(dimension, Square()));
  for(dataype d0 = 0; d0 < dimension; ++d0)
  {
    for(dataype d1 = 0; d1 < dimension; ++d1)
    {
      grid[d0][d1].possible_values = unordered_set<dataype>({d0});
      grid[d0][d1].certain = true;
    }
  }
  Board *b = new Board(grid, dimension);
  assert(b && b->dimension == dimension && b->grid.size() == dimension && b->grid[0].size() == dimension && "test_board_constructor1: failed to make board");
  for(dataype d0 = 0; d0 < dimension; ++d0)
  {
    for(dataype d1 = 0; d1 < dimension; ++d1)
    {
      assert(b->grid[d0][d1].certain && b->grid[d0][d1].possible_values.size() == 1 && b->grid[d0][d1].possible_values.count(d0) && "test_board_constructor1: incorrect square value in grid");
    }
  }
}

int main()
{
  test_square_constructor0();
  test_square_constructor1();
  test_square_constructor2();
  test_board_constructor0();
  test_board_constructor1();
  return 0;
}
