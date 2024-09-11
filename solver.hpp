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

    int dfs(Puzzle p, std::vector<Direction> &path,
            std::unordered_set<uint64_t> &visited, int walked, int limit);
};

#endif