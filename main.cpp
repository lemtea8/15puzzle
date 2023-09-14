#include <chrono>
#include <iostream>

#include "hex.hpp"
#include "puzzle.hpp"
#include "solver.hpp"

void print_answer(std::vector<Direction> &answer) {
    for (int i = 0; i < answer.size(); i++) {
        switch (answer[i]) {
        case UP:
            std::cout << "↑";
            break;
        case DOWN:
            std::cout << "↓";
            break;
        case LEFT:
            std::cout << "←";
            break;
        case RIGHT:
            std::cout << "→";
            break;
        default:
            break;
        }
        if ((i + 1) % 5 == 0) {
            std::cout << " ";
        }
    }
    std::cout << ", " << answer.size() << " steps" << std::endl;
}

int main() {
    std::string input;

    while (std::cin >> input) {
        Puzzle p(input);
        Solver solver;
        if (!p.solvable()) {
            std::cout << "unsolvable" << std::endl;
            continue;
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto ans = solver.solve(p);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end -
            start);

        print_answer(ans);
        std::cout << "time:" << duration.count() << "ms" << std::endl;
    }

    return 0;
}
