#include "../src/utils.h"

void test_utils()
{
  Board *b = read_board("../test/boards/board0.txt");
  print_board(b);
}

void test_checkpoint0()
{
  Board *b = read_board("../test/boards/board3.txt");
  frontier s;
  score_fn fn = basic_score_fn;
  Status status = checkpoint(b, s, fn);
  pair<Board*,BoardMetric> stored_state = s.top();
  assert(status && b == stored_state.first && stored_state.second.score == b->dimension*b->dimension && stored_state.second.best_square_coordinates[0] == b->dimension && stored_state.second.best_square_coordinates[0] == b->dimension && "test test_checkpoint0: failed");
}

void test_checkpoint1()
{
  Board *b = read_board("../test/boards/board2.txt");
  frontier s;
  score_fn fn = basic_score_fn;
  Status status = checkpoint(b, s, fn);
  pair<Board*,BoardMetric> stored_state = s.top();
  assert(status && b == stored_state.first && stored_state.second.score == (score_t) 113 && stored_state.second.best_square_coordinates[0] == 1 && stored_state.second.best_square_coordinates[1] == 7 && "test test_checkpoint1: failed");
}

void test_guess0()
{
  Board *b = read_board("../test/boards/board2.txt");
  Status status = guess(b, {0,0}, 6);
  assert(status == fail && "test_guess0: failed");
}

void test_guess1()
{
  Board *b = read_board("../test/boards/board2.txt");
  vector<size_t> cor({8,7});
  dataype x = 6;
  Status status = guess(b, cor, x);
  assert(status == pass && b->grid[cor[0]][cor[1]].certain && b->grid[cor[0]][cor[1]].possible_values.size() == 1 && b->grid[cor[0]][cor[1]].possible_values.count(x) == 1 && "test_guess1: failed");
}

void test_refresh_states0()
{
  Board *b = read_board("../test/boards/board2.txt");
  vector<size_t> cor({8,7});
  dataype x = 6;
  Status status_guess = guess(b, cor, x);
  Status status_refresh = refresh_states(b, cor);
  assert(status_guess == pass && b->grid[cor[0]][cor[1]].certain && b->grid[cor[0]][cor[1]].possible_values.size() == 1 && b->grid[cor[0]][cor[1]].possible_values.count(x) == 1 && "test_refresh_states0: guess failed");
  assert(status_refresh == pass && !b->grid[8][8].certain && b->grid[8][8].possible_values.size() == 8 && "test_refresh_states0: refresh failed");
}

void test_refresh_states1()
{
  Board *b = read_board("../test/boards/board2.txt");
  vector<size_t> cor({8,7});
  dataype x = 6;
  Status status_guess = guess(b, cor, x);
  Status status_refresh0 = refresh_states(b, cor);
  Status status_refresh1 = refresh_states(b, cor);
  assert(status_guess == pass && b->grid[cor[0]][cor[1]].certain && b->grid[cor[0]][cor[1]].possible_values.size() == 1 && b->grid[cor[0]][cor[1]].possible_values.count(x) == 1 && "test_refresh_states0: guess failed");
  assert(status_refresh0 == pass && !b->grid[8][8].certain && b->grid[8][8].possible_values.size() == 8 && "test_refresh_states0: refresh failed");
  assert(status_refresh1 == fail && !b->grid[8][8].certain && b->grid[8][8].possible_values.size() == 8 && "test_refresh_states0: refresh failed");
}


int main()
{
  test_utils();
  test_checkpoint0();
  test_checkpoint1();
  test_guess0();
  test_guess1();
  test_refresh_states0();
  test_refresh_states1();
  return 0;
}
