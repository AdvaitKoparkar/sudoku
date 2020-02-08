#include "../src/rules.h"
#include "../src/utils.h"

void test_rule0_board0()
{
  Board *b = read_board("../test/boards/board0.txt");
  assert(pass == rule0(b) && "test_rule0_board0: failed");
}

void test_rule0_board1()
{
  Board *b = read_board("../test/boards/board1.txt");
  assert(pass == rule0(b) && "test_rule0_board1: failed");
}

void test_rule0_board2()
{
  Board *b = read_board("../test/boards/board2.txt");
  assert(pass == rule0(b) && "test_rule0_board2: failed");
}

void test_rule0_board3()
{
  Board *b = read_board("../test/boards/board3.txt");
  assert(pass == rule0(b) && "test_rule0_board3: failed");
}

void test_rule1_board0()
{
  Board *b = read_board("../test/boards/board0.txt");
  assert(rule1(b) == pass && "test_rule1_board0: failed");
}

void test_rule1_board1()
{
  Board *b = read_board("../test/boards/board1.txt");
  assert(rule1(b) == pass && "test_rule1_board1: failed");
}

void test_rule1_board2()
{
  Board *b = read_board("../test/boards/board2.txt");
  assert(rule1(b) == fail && "test_rule1_board2: failed");
}

void test_rule1_board3()
{
  Board *b = read_board("../test/boards/board3.txt");
  assert(rule1(b) == pass && "test_rule1_board3: failed");
}

void test_rule2_board0()
{
  Board *b = read_board("../test/boards/board0.txt");
  assert(rule2(b) == pass && "test_rule2_board0: failed");
}

void test_rule2_board1()
{
  Board *b = read_board("../test/boards/board1.txt");
  assert(rule2(b) == pass && "test_rule2_board1: failed");
}

void test_rule2_board2()
{
  Board *b = read_board("../test/boards/board2.txt");
  assert(rule2(b) == fail && "test_rule2_board2: failed");
}

void test_rule2_board3()
{
  Board *b = read_board("../test/boards/board3.txt");
  assert(rule2(b) == pass && "test_rule2_board3: failed");
}

void test_rule3_board0()
{
  Board *b = read_board("../test/boards/board0.txt");
  assert(rule3(b) == pass && "test_rule3_board0: failed");
}

void test_rule3_board1()
{
  Board *b = read_board("../test/boards/board1.txt");
  assert(rule3(b) == pass && "test_rule3_board1: failed");
}

void test_rule3_board2()
{
  Board *b = read_board("../test/boards/board2.txt");
  assert(rule3(b) == fail && "test_rule3_board2: failed");
}

void test_rule3_board3()
{
  Board *b = read_board("../test/boards/board3.txt");
  assert(rule3(b) == pass && "test_rule3_board3: failed");
}

void test_complete_board0()
{
  Board *b = read_board("../test/boards/board0.txt");
  assert(iscomplete(b) == fail && "test_complete_board0: failed");
}

void test_complete_board1()
{
  Board *b = read_board("../test/boards/board1.txt");
  assert(iscomplete(b) == fail && "test_complete_board1: failed");
}

void test_complete_board2()
{
  Board *b = read_board("../test/boards/board2.txt");
  assert(iscomplete(b) == fail && "test_complete_board2: failed");
}

void test_complete_board3()
{
  Board *b = read_board("../test/boards/board3.txt");
  assert(iscomplete(b) == pass && "test_complete_board3: failed");
}

void test_rule0()
{
  test_rule0_board0();
  test_rule0_board1();
  test_rule0_board2();
  test_rule0_board3();
}

void test_rule1()
{
  test_rule1_board0();
  test_rule1_board1();
  test_rule1_board2();
  test_rule1_board3();
}

void test_rule2()
{
  test_rule2_board0();
  test_rule2_board1();
  test_rule2_board2();
}

void test_rule3()
{
  test_rule3_board0();
  test_rule3_board1();
  test_rule3_board2();
  test_rule3_board3();
}

void test_complete()
{
  test_complete_board0();
  test_complete_board1();
  test_complete_board2();
  test_complete_board3();
}

int main()
{
  test_rule0();
  test_rule1();
  test_rule2();
  test_rule3();
  test_complete();
  return 0;
}
