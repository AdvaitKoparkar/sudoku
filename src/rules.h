#ifndef RULES_H
#define RULES_H
#include "sudoku.h"
#include "indexing.h"
#include "utils.h"

Status rule0(Board *b)
{
  if(!b) return fail;
  for(size_t d0 = 0; d0 < b->dimension; ++d0)
  {
    for(size_t d1 = 0; d1 < b->dimension; ++d1)
    {
      if(b->grid[d0][d1].possible_values.size() == 0) return fail;
      for(unordered_set<dataype>::iterator it = b->grid[d0][d1].possible_values.begin(); it != b->grid[d0][d1].possible_values.end(); ++it)
      {
        if((*it) > b->dimension) return fail;
      }
    }
  }
  return pass;
}

Status rule1(Board *b)
{
  if(!b) return fail;
  unordered_set<dataype> vals_in_row;
  vector<vector<size_t> > row_coordinates;

  for(size_t r = 0; r < b->dimension; ++r)
  {
    vals_in_row.clear();
    row_coordinates.clear();
    if(!get_row_coordinates(r, b->dimension, row_coordinates)) return fail;
    for(vector<size_t> cor : row_coordinates)
    {
      if(b->grid[cor[0]][cor[1]].certain)
      {
        dataype val = *(b->grid[cor[0]][cor[1]].possible_values.begin());
        if(vals_in_row.count(val))
        {
          return fail;
        }
        vals_in_row.insert(val);
      }
    }
  }
  return pass;
}

Status rule2(Board *b)
{
  if(!b) return fail;
  unordered_set<dataype> vals_in_col;
  vector<vector<size_t> > col_coordinates;

  for(size_t c = 0; c < b->dimension; ++c)
  {
    vals_in_col.clear();
    col_coordinates.clear();
    if(!get_col_coordinates(c, b->dimension, col_coordinates)) return fail;
    for(vector<size_t> cor : col_coordinates)
    {
      if(b->grid[cor[0]][cor[1]].certain)
      {
        dataype val = *(b->grid[cor[0]][cor[1]].possible_values.begin());
        if(vals_in_col.count(val)) return fail;
        vals_in_col.insert(val);
      }
    }
  }
  return pass;
}

Status rule3(Board *b)
{
  if(!b) return fail;
  unordered_set<dataype> vals_in_minigrid;
  vector<vector<size_t> > minigrid_coordinates;

  for(size_t minigrid_idx = 0; minigrid_idx < b->dimension; ++minigrid_idx)
  {
    vals_in_minigrid.clear();
    minigrid_coordinates.clear();
    if(!get_grid_coordinates(minigrid_idx, b->dimension, minigrid_coordinates)) return fail;
    for(vector<size_t> cor : minigrid_coordinates)
    {
      if(b->grid[cor[0]][cor[1]].certain)
      {
        dataype val = *(b->grid[cor[0]][cor[1]].possible_values.begin());
        if(vals_in_minigrid.count(val)) return fail;
        vals_in_minigrid.insert(val);
      }
    }
  }
  return pass;
}

Status isvalid(Board *b)
{
  if(rule0(b) && rule1(b) && rule2(b) && rule3(b)) return pass;
  return fail;
}

Status iscomplete(Board *b)
{
  if(!isvalid(b)) return fail;
  for(size_t r = 0; r < b->dimension; ++r)
  {
    for(size_t c = 0; c < b->dimension; ++c)
    {
      if(!b->grid[r][c].certain) return fail;
    }
  }
  return pass;
}

#endif
