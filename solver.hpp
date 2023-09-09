#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include <vector>

#include "puzzle.hpp"
#include "direction.hpp"

class Solver {
  public:
    Solver();
    std::vector<Direction> solve(Puzzle puzzle);

  private:
    uint size;
    Puzzle puzzle;
};

#endif