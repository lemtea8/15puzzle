#ifndef __PUZZLE_HPP__
#define __PUZZLE_HPP__

#include <cstdint>
#include <string>

#include "direction.hpp"

class Puzzle {
  public:
    Puzzle();
    Puzzle(uint64_t bits);
    Puzzle(const std::string &input);
    uint8_t at(int n);
    void set(int n, uint8_t val);
    void swap(int i, int j);
    int heuristic();
    bool solvable();
    bool is_goal();
    bool move(Direction dir);
    std::string to_string();
    std::string to_visualize_string();
    uint64_t get_bits();

  private:
    int zero_position;
    int heuristic_v;
    uint64_t bits;

    int calculate_heuristic();
    int find_zero_position();
};

#endif