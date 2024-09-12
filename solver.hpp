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
    int count;
    uint size;
    Puzzle puzzle;
    std::vector<Direction> path;
    // for checking if it's already visited within the path
    std::unordered_set<uint64_t> visited;

    int dfs(Puzzle p, int walked, int limit);
};

#endif