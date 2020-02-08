cmake_minimum_required(VERSION 3.9)
set (CMAKE_CXX_STANDARD 14)

project(sudoku VERSION 1.0)

add_subdirectory(${CMAKE_SOURCE_DIR}/test)

enable_testing()
add_test(NAME test_basic_board_fn COMMAND test_basic_board_fn)
add_test(NAME test_indexing COMMAND test_indexing)
add_test(NAME test_rules COMMAND test_rules)
add_test(NAME test_utils COMMAND test_utils)
add_test(NAME test_solver COMMAND test_solver)
