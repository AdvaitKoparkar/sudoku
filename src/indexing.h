#ifndef INDEXING_H
#define INDEXING_H
#include "../src/sudoku.h"

Status isvalidcoordinates(const vector<size_t> &coordinates, const size_t dimension)
{
  if(coordinates.size() != 2) return fail;
  if(coordinates[0] < dimension && coordinates[1] < dimension) return pass;
  return fail;
}

Status isvalidindex(const size_t &idx, const size_t &dimension)
{
  if(idx < dimension*dimension) return pass;
  return fail;
}

Status get_coordinates(const size_t &idx, const size_t &dimension, vector<size_t> &coordinates)
{
  if(!isvalidindex(idx, dimension) || coordinates.size() != 2) return fail;
  coordinates[0] = idx/dimension;
  coordinates[1] = idx%dimension;
  return pass;
}

Status get_index(const vector<size_t> &coordinates, const size_t &dimension, size_t &idx)
{
  if(!isvalidcoordinates(coordinates, dimension)) return fail;
  idx = coordinates[0] * dimension + coordinates[1];
  return pass;
}

Status get_row_coordinates(const size_t &row, const size_t &dimension, vector<vector<size_t> > &coordinates)
{
  if(row >= dimension) return fail;
  coordinates.clear();
  for(size_t c = 0; c < dimension; ++c) coordinates.push_back({row,c});
  return pass;
}

Status get_col_coordinates(const size_t &col, const size_t &dimension, vector<vector<size_t> > &coordinates)
{
  if(col >= dimension) return fail;
  coordinates.clear();
  for(size_t r = 0; r < dimension; ++r) coordinates.push_back({r,col});
  return pass;
}

Status get_grid_coordinates(const size_t &grid, const size_t &dimension, vector<vector<size_t> > &coordinates)
{
  if(grid >= dimension) return fail;
  coordinates.clear();
  size_t sqrt_dimension = (size_t) sqrt(dimension), r_start, c_start;
  r_start = (grid/sqrt_dimension) * sqrt_dimension;
  c_start = (grid%sqrt_dimension) * sqrt_dimension;
  for(size_t r = r_start; r < r_start + sqrt_dimension; ++r)
  {
    for(size_t c = c_start; c < c_start + sqrt_dimension; ++c)
    {
      coordinates.push_back({r,c});
    }
  }
  return pass;
}

Status get_grid(const vector<size_t> &coordinates, const size_t &dimension, size_t &grid)
{
  if(!isvalidcoordinates(coordinates, dimension)) return fail;
  size_t sqrt_dimension = (size_t) sqrt(dimension);
  grid = (coordinates[0] / sqrt_dimension) * sqrt_dimension + (coordinates[1] / sqrt_dimension);
  return pass;
}

Status get_all_coordinates(const size_t &dimension, vector<vector<size_t> > &coordinates)
{
  coordinates.clear();
  for(size_t r = 0; r < dimension; ++r)
  {
    for(size_t c = 0; c < dimension; ++c)
    {
      coordinates.push_back({r,c});
    }
  }
  return pass;
}

#endif
