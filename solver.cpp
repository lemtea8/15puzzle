#include "solver.hpp"

#include <climits>
#include <cstdint>
#include <iostream>

const int FOUND = -1;

Solver::Solver() { this->count = 0; }

int Solver::dfs(Puzzle p, std::vector<Direction> &path,
                std::unordered_set<uint64_t> &visited, int walked, int limit) {
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
        if (visited.count(tmp.get_bits()) != 0) {
            continue;
        }
        path.push_back(dir);
        visited.insert(tmp.get_bits());
        int res = dfs(tmp, path, visited, walked + 1, limit);
        if (res == FOUND) {
            return FOUND;
        }
        path.pop_back();
        visited.erase(tmp.get_bits());
        if (res < min) {
            min = res;
        }
    }
    return min;
}

std::vector<Direction> Solver::solve(Puzzle puzzle) {
    int t = puzzle.heuristic();
    // act like a stack
    std::vector<Direction> path;
    // check if it's already visited within the path
    std::unordered_set<uint64_t> visited;
    this->count = 0;

    // IDA*
    while (true) {
        std::cout << "\rdepth: " << t << std::flush;
        t = dfs(puzzle, path, visited, 0, t);
        if (t == FOUND) {
            break;
        }
    }
    std::cout << std::endl << "nodes count: " << count << std::endl;

    return path;
}
