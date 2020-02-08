#include "../src/solver.h"

void test_solver0()
{
  Board *b = read_board("../test/boards/board3.txt");
  assert(solve(b) && "test_solver0: failed");
}

void test_solver1()
{
  Board *b = read_board("../test/boards/board2.txt");
  assert(!solve(b) && "test_solver1: failed");
}

void test_solver2()
{
  Board *b = read_board("../test/boards/board4.txt");
  assert(solve(b) && "test_solver2: failed");
}

void test_solver3()
{
  Board *b = read_board("../test/boards/board5.txt");
  assert(solve(b) && "test_solver3: failed");
}

int main()
{
  test_solver0();
  test_solver1();
  test_solver2();
  test_solver3();
  return 0;
}
