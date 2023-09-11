#include "solver.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <unordered_set>

class State {
  public:
    State(State *parent, uint64_t bits, int walked, int heuristic,
          Direction dir) {
        this->parent = parent;
        this->bits = bits;
        this->walked = walked;
        this->heuristic = heuristic;
        this->dir = dir;
    }
    uint64_t get_bits() { return this->bits; }
    int heuristic;
    int walked;
    State *parent;
    Direction dir;

  private:
    uint64_t bits;
};

class StateComparetor {
  public:
    bool operator()(const State *i, const State *j);
};

bool StateComparetor::operator()(const State *i, const State *j) {
    return i->walked + i->heuristic > j->walked + j->heuristic;
}

Solver::Solver() {}

std::vector<Direction> Solver::solve(Puzzle puzzle) {
    std::priority_queue<State *, std::vector<State *>, StateComparetor> pq;
    std::vector<State *> used;

    // record visited states
    std::unordered_set<uint64_t> visited;
    int walked = 0;
    int pq_max = 0;

    State *root =
        new State(nullptr, puzzle.get_bits(), walked, puzzle.heuristic(), UP);
    pq.push(root);
    State *last = nullptr;

    while (!pq.empty()) {
        if (pq.size() > pq_max) {
            pq_max = pq.size();
        }

        State *curr = pq.top();
        visited.insert(curr->get_bits());
        last = curr;
        walked = curr->walked + 1;
        pq.pop();
        used.push_back(curr);

        Puzzle p(curr->get_bits());
        if (p.is_goal()) {
            break;
        }

        for (auto dir : {UP, DOWN, LEFT, RIGHT}) {
            Puzzle tmp = p;
            tmp.move(dir);
            // only append to queue if not visited
            if (visited.count(tmp.get_bits()) == 0) {
                State *next = new State(curr, tmp.get_bits(), walked,
                                        tmp.heuristic(), dir);
                pq.push(next);
                visited.insert(tmp.get_bits());
            }
        }
    }

    std::vector<Direction> answer;
    while (true) {
        if (last->parent == nullptr) {
            break;
        }
        answer.push_back(last->dir);
        last = last->parent;
    }
    std::reverse(answer.begin(), answer.end());

    while (!pq.empty()) {
        State *s = pq.top();
        pq.pop();
        delete s;
    }
    for (auto s : used) {
        delete s;
    }

    return answer;
}
