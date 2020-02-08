#include "../src/indexing.h"

void test_valid(size_t r, size_t c, size_t dimension)
{
  vector<size_t> expected_coordinates({r,c}), coordinates({89850,65650});
  size_t expected_idx = r*dimension + c, idx = 56650;
  Status status_backward = get_index(expected_coordinates, dimension, idx);
  Status status_forward = get_coordinates(idx, dimension, coordinates);
  assert(status_backward == pass && expected_idx == idx && "test_indexing: incorrect valid index");
  assert(status_forward == pass && expected_coordinates == coordinates && "test_indexing: incorrect valid coordinates");
}

void test_invalid(size_t r, size_t c, size_t dimension)
{
  vector<size_t> expected_coordinates({r,c}), coordinates({89850,65650});
  size_t expected_idx = r*dimension + c, idx = 56650;
  Status status_backward = get_index(expected_coordinates, dimension, idx);
  Status status_forward = get_coordinates(idx, dimension, coordinates);
  assert(status_backward == fail && "test_indexing: incorrect invalid index");
  assert(status_forward == fail && "test_indexing: incorrect invalid coordinates");
}

void test_row_coordinates0()
{
  vector<vector<size_t> > row_coordinates, expected_row_coordinates;
  size_t row = 5, dimension = 8;
  for(size_t c = 0; c < dimension; ++c) expected_row_coordinates.push_back({row, c});
  Status s = get_row_coordinates(row, dimension, row_coordinates);
  for(size_t i = 0; i < expected_row_coordinates.size(); ++i)
  {
    assert(s == pass && row_coordinates[i][0] == expected_row_coordinates[i][0] && row_coordinates[i][1] == expected_row_coordinates[i][1] && "test_row_coordinates0: failed""test_row_coordinates0: failed");
  }
}

void test_col_coordinates0()
{
  vector<vector<size_t> > col_coordinates, expected_col_coordinates;
  size_t col = 7, dimension = 9;
  for(size_t r = 0; r < dimension; ++r) expected_col_coordinates.push_back({r, col});
  Status s = get_col_coordinates(col, dimension, col_coordinates);
  for(size_t i = 0; i < expected_col_coordinates.size(); ++i)
  {
    assert(s == pass && col_coordinates[i][0] == expected_col_coordinates[i][0] && col_coordinates[i][1] == expected_col_coordinates[i][1] && "test_col_coordinates0: failed""test_row_coordinates0: failed");
  }
}

void test_grid_coordinates0()
{
  vector<vector<size_t> > grid_coordinates, expected_grid_coordinates;
  size_t grid = 6, dimension = 9, g = 84;
  expected_grid_coordinates.push_back({6,0});
  expected_grid_coordinates.push_back({6,1});
  expected_grid_coordinates.push_back({6,2});
  expected_grid_coordinates.push_back({7,0});
  expected_grid_coordinates.push_back({7,1});
  expected_grid_coordinates.push_back({7,2});
  expected_grid_coordinates.push_back({8,0});
  expected_grid_coordinates.push_back({8,1});
  expected_grid_coordinates.push_back({8,2});
  Status s = get_grid_coordinates(grid, dimension, grid_coordinates);
  Status s_grid;
  for(size_t i = 0; i < expected_grid_coordinates.size(); ++i)
  {
    s_grid = get_grid(expected_grid_coordinates[i], dimension, g);
    assert(s == pass && grid_coordinates[i][0] == expected_grid_coordinates[i][0] && grid_coordinates[i][1] == expected_grid_coordinates[i][1] && "test_grid_coordinates0: failed");
    assert(s_grid == pass && g == grid && "test_grid_coordinates0: failed get_grid test");
  }
}

void test_grid_coordinates1()
{
  vector<vector<size_t> > grid_coordinates, expected_grid_coordinates;
  size_t grid = 4, dimension = 9, g = 84;
  expected_grid_coordinates.push_back({3,3});
  expected_grid_coordinates.push_back({3,4});
  expected_grid_coordinates.push_back({3,5});
  expected_grid_coordinates.push_back({4,3});
  expected_grid_coordinates.push_back({4,4});
  expected_grid_coordinates.push_back({4,5});
  expected_grid_coordinates.push_back({5,3});
  expected_grid_coordinates.push_back({5,4});
  expected_grid_coordinates.push_back({5,5});
  Status s = get_grid_coordinates(grid, dimension, grid_coordinates);
  Status s_grid;
  for(size_t i = 0; i < expected_grid_coordinates.size(); ++i)
  {
    s_grid = get_grid(expected_grid_coordinates[i], dimension, g);
    assert(s == pass && grid_coordinates[i][0] == expected_grid_coordinates[i][0] && grid_coordinates[i][1] == expected_grid_coordinates[i][1] && "test_grid_coordinates1: failed");
    assert(s_grid == pass && g == grid && "test_grid_coordinates1: failed get_grid test");
  }
}

void test_indexing()
{
  size_t dimension = 9;
  for(size_t r = 0; r < dimension+807; ++r)
  {
    for(size_t c = 0; c < dimension+890; ++c)
    {
      if(isvalidcoordinates({r,c}, dimension)) test_valid(r, c, dimension);
      else test_invalid(r, c, dimension);
    }
  }
}

void test_grp_coordinates()
{
  test_row_coordinates0();
  test_col_coordinates0();
  test_grid_coordinates0();
  test_grid_coordinates1();
}

int main()
{
  test_indexing();
  test_grp_coordinates();
  return 0;
}
