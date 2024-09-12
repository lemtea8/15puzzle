#include "solver.hpp"

#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>

const int FOUND = -1;

Solver::Solver() { this->count = 0; }

int Solver::dfs(Puzzle p, int walked, int limit) {
    this->count++;
    int h = p.heuristic();
    int f = walked + h;

    if (f > limit) {
        return f;
    }
    if (p.is_goal()) {
        return FOUND;
    }

    int min = INT_MAX;
    for (auto dir : {UP, DOWN, LEFT, RIGHT}) {
        Puzzle tmp = p;
        if (!tmp.move(dir)) {
            continue;
        }
        if (this->visited.count(tmp.get_bits()) != 0) {
            continue;
        }
        this->visited.insert(tmp.get_bits());
        int res = dfs(tmp, walked + 1, limit);
        if (res == FOUND) {
            this->path.push_back(dir);
            return FOUND;
        }
        this->visited.erase(tmp.get_bits());
        if (res < min) {
            min = res;
        }
    }
    return min;
}

std::vector<Direction> Solver::solve(Puzzle puzzle) {
    this->path.clear();
    this->visited.clear();
    this->count = 0;

    int t = puzzle.heuristic();

    // IDA*
    while (true) {
        std::cout << "\rdepth: " << t << std::flush;
        t = dfs(puzzle, 0, t);
        if (t == FOUND) {
            break;
        }
    }
    std::cout << std::endl << "nodes count: " << count << std::endl;
    std::reverse(this->path.begin(), this->path.end());

    return this->path;
}
