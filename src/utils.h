#ifndef UTILS_H
#define UTILS_H
#include "sudoku.h"
#include "indexing.h"

typedef long score_t;

typedef struct BoardMetric
{
  score_t score;
  vector<size_t> best_square_coordinates;
  BoardMetric(score_t s, vector<size_t> cor) : score(s), best_square_coordinates(cor) {}
} BoardMetric;

struct MetricComparator
{
  bool operator () (const pair<const Board*, BoardMetric> &l, const pair<const Board*, BoardMetric> &r)
  {
    return l.second.score >= r.second.score;
  }
};

typedef Status (*score_fn) (const Board *b, BoardMetric &metric);
typedef priority_queue<pair<Board*,BoardMetric>, vector<pair<Board*, BoardMetric> >, MetricComparator> frontier;

Status get_metric(const Board *b, score_fn fn, BoardMetric &metric)
{
  return (*fn)(b, metric);
}

Status basic_score_fn(const Board *b, BoardMetric &metric)
{
  metric.score = 0;
  vector<vector<size_t> > all_coordinates;
  metric.best_square_coordinates = vector<size_t>({b->dimension, b->dimension});
  size_t min_possible_val = b->dimension+1;

  if(!get_all_coordinates(b->dimension, all_coordinates)) return fail;
  for(vector<size_t> cor : all_coordinates)
  {
    size_t pos_vals = b->grid[cor[0]][cor[1]].possible_values.size();
    metric.score += pos_vals;
    if(min_possible_val > pos_vals && !b->grid[cor[0]][cor[1]].certain)
    {
      min_possible_val = pos_vals;
      metric.best_square_coordinates = vector<size_t>(cor);
    }
  }
  return pass;
}

void print_board(Board *b)
{
  size_t idx;

  if(!b) return;
  for(size_t r = 0; r < b->dimension; ++r)
  {
    for(size_t c = 0; c < b->dimension; ++c)
    {
      if(!b->grid[r][c].certain)
      {
        cout << "-";
      }
      else
      {
        cout << *(b->grid[r][c].possible_values.begin());
      }
    }
    cout << endl;
  }
}

Board* read_board(string filename)
{
  ifstream fh(filename);
  size_t dimension;
  dataype x;
  Board *b;

  assert(fh.is_open() && "could not open board");
  fh >> dimension;
  b = new Board(dimension);
  assert(b && "out of memory");
  for(size_t r = 0; r < dimension; ++r)
  {
    for(size_t c = 0; c < dimension; ++c)
    {
      fh >> x;
      b->grid[r][c].certain = false;
      b->grid[r][c].possible_values.clear();
      if(x == 0)
      {
        for(dataype val = 1; val <= dimension; ++val) b->grid[r][c].possible_values.insert(val);
      }
      else
      {
        b->grid[r][c].certain = true;
        b->grid[r][c].possible_values.insert(x);
      }
    }
  }
  return b;
}

Status checkpoint(Board *b, frontier &s, score_fn fn)
{
  if(!b) return fail;
  BoardMetric metric(b->dimension*b->dimension*b->dimension+1, {b->dimension, b->dimension});
  if(!get_metric(b, fn, metric)) return fail;
  s.push({b, metric});
  return pass;
}

Status guess(Board *b, const vector<size_t> &coordinates, const dataype &guess_val)
{
  if(!isvalidcoordinates(coordinates, b->dimension) || b->grid[coordinates[0]][coordinates[1]].certain) return fail;
  b->grid[coordinates[0]][coordinates[1]].certain = true;
  b->grid[coordinates[0]][coordinates[1]].possible_values = unordered_set<dataype>({guess_val});
  return pass;
}

Status refresh_states(Board *b, const vector<size_t> &coordinates)
{
  if(!b || !isvalidcoordinates(coordinates, b->dimension) || !b->grid[coordinates[0]][coordinates[1]].certain) return fail;
  vector<vector<size_t> > row_coordinates, col_coordinates, grid_coordinates;
  size_t grid_idx = b->dimension * b->dimension;
  Status s = fail;
  dataype coordinates_value = *(b->grid[coordinates[0]][coordinates[1]].possible_values.begin());

  if(!get_grid(coordinates, b->dimension, grid_idx)) return fail;
  if(!get_row_coordinates(coordinates[0], b->dimension, row_coordinates)) return fail;
  if(!get_col_coordinates(coordinates[1], b->dimension, col_coordinates)) return fail;
  if(!get_grid_coordinates(grid_idx, b->dimension, grid_coordinates)) return fail;

  for(vector<size_t> cor : row_coordinates)
  {
    if(cor[0] == coordinates[0] && cor[1] == coordinates[1] || b->grid[cor[0]][cor[1]].certain) continue;
    if(b->grid[cor[0]][cor[1]].possible_values.count(coordinates_value))
    {
      s = pass;
      b->grid[cor[0]][cor[1]].possible_values.erase(coordinates_value);
    }
  }

  for(vector<size_t> cor : col_coordinates)
  {
    if(cor[0] == coordinates[0] && cor[1] == coordinates[1] || b->grid[cor[0]][cor[1]].certain) continue;
    if(b->grid[cor[0]][cor[1]].possible_values.count(coordinates_value))
    {
      s = pass;
      b->grid[cor[0]][cor[1]].possible_values.erase(coordinates_value);
    }
  }

  for(vector<size_t> cor : grid_coordinates)
  {
    if(cor[0] == coordinates[0] && cor[1] == coordinates[1] || b->grid[cor[0]][cor[1]].certain) continue;
    if(b->grid[cor[0]][cor[1]].possible_values.count(coordinates_value))
    {
      s = pass;
      b->grid[cor[0]][cor[1]].possible_values.erase(coordinates_value);
    }
  }

  return s;

}

#endif
