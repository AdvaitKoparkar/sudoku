#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"
#include "rules.h"
#include "utils.h"
#include "indexing.h"

Status solve(Board *b)
{
  Status status = fail;
  frontier frnt;
  score_fn fn = basic_score_fn;
  string err_msg;
  vector<vector<size_t> > all_coordinates;
  if(!get_all_coordinates(b->dimension, all_coordinates))
  {
    err_msg = "could not get all coordinates";
    goto EXIT;
  }

  if(!isvalid(b))
  {
    err_msg = "invalid state cannot be solved";
    goto EXIT;
  }

  if(!checkpoint(b, frnt, fn))
  {
    err_msg = "failed to checkpoint initial state";
    goto EXIT;
  }

  while(!frnt.empty())
  {
    pair<Board*, BoardMetric> state = frnt.top();
    frnt.pop();

    Board *b = state.first;
    BoardMetric metric = state.second;

    if(!isvalid(b)) continue;
    if(iscomplete(b))
    {
      status = pass;
      err_msg = "solved!";
      print_board(b);
      goto EXIT;
    }

    Status refresh = fail;
    for(vector<size_t> cor : all_coordinates)
    {
      if(refresh_states(b, cor)) refresh = pass;
    }
    if(!refresh)
    {
      dataype val = *(b->grid[metric.best_square_coordinates[0]][metric.best_square_coordinates[1]].possible_values.begin());
      Board *copy_board = new Board(*b);
      if(!guess(copy_board, metric.best_square_coordinates, val))
      {
        err_msg = "error guessing value";
        goto EXIT;
      }
      checkpoint(copy_board, frnt, fn);
      b->grid[metric.best_square_coordinates[0]][metric.best_square_coordinates[1]].possible_values.erase(val);
    }
    checkpoint(b, frnt, fn);
  }

EXIT:
  cout << err_msg << endl;
  return status;
}

#endif
