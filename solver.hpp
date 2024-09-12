#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include <unordered_set>
#include <vector>

#include "direction.hpp"
#include "puzzle.hpp"

class Solver {
  public:
    Solver();
    std::vector<Direction> solve(Puzzle puzzle);

  private:
    uint64_t count;
    Puzzle puzzle;
    std::vector<Direction> path;
    // for checking if it's already visited within the path
    std::vector<uint64_t> visited;

    int dfs(Puzzle p, int walked, int limit);
};

#endif