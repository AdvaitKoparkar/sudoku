#ifndef SUDOKU_H
#define SUDOKU_H
#include<bits/stdc++.h>

using namespace std;

typedef int dataype;
typedef enum Status
{
  fail,
  pass
} Status;

typedef struct Square
{
  bool certain;
  unordered_set<dataype> possible_values;
  Square() : certain(false), possible_values(unordered_set<dataype>()) {}
  Square(dataype x) : possible_values({x}), certain(true) {}
  Square(unordered_set<dataype> vals) : possible_values(vals), certain(false) {}
} Square;

typedef struct Board
{
  size_t dimension;
  vector<vector<Square> > grid;
  Board(size_t dim) : dimension(dim)
  {
    unordered_set<dataype> possible_values;
    for(int i = 1; i <= dimension; ++i) possible_values.insert(i);
    grid = vector<vector<Square>> (dimension, vector<Square>(dimension, Square(possible_values)));
  }
  Board(vector<vector<Square> > g, size_t dim) : grid(g), dimension(dim) {}
} Board;

#endif
