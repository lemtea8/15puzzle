#include "puzzle.hpp"
#include "hex.hpp"

Puzzle::Puzzle() {
    this->bits = 0;
    this->heuristic_v = 0;
}

Puzzle::Puzzle(uint64_t bits) {
    this->bits = bits;
    this->heuristic_v = calculate_heuristic();
}

// "0" stands for the blank
Puzzle::Puzzle(const std::string &input) {
    this->bits = 0;
    for (int i = 0; i < input.size(); i++) {
        char c = input[i];
        uint64_t num = hex_to_int(c);
        // each cell takes four bits (0~F)
        this->bits |= num << (i * 4);
    }
    this->zero_position = find_zero_position();
    this->heuristic_v = calculate_heuristic();
}

uint8_t Puzzle::at(int n) {
    uint64_t mask = uint64_t(0b1111) << (n * 4);
    return (this->bits & mask) >> (n * 4);
}

void Puzzle::set(int n, uint8_t val) {
    uint64_t mask = ~(uint64_t(0b1111) << (n * 4));
    this->bits &= mask; // set the target area to zero
    uint64_t valmask = uint64_t(val) << (n * 4);
    this->bits |= valmask;
}

void Puzzle::swap(int i, int j) {
    uint64_t tmp = this->at(i);
    this->set(i, this->at(j));
    this->set(j, tmp);
}

uint64_t Puzzle::get_bits() { return this->bits; }

std::string Puzzle::to_string() {
    std::string str;
    for (int i = 0; i < 16; i++) {
        str += int_to_hex(this->at(i));
    }
    return str;
}

std::string Puzzle::to_visualize_string() {
    std::string str;
    for (int i = 0; i < 16; i++) {
        str += int_to_hex(this->at(i));
        if ((i + 1) % 4 == 0 && i != 15) {
            str += '\n';
        }
    }
    return str;
}

// https://en.wikipedia.org/wiki/15_puzzle#solvability:~:text=%5Bedit%5D-,Solvability,-%5Bedit%5D
bool Puzzle::solvable() {
    int inversion_count = 0;
    for (uint32_t i = 0; i < 15; i++) {
        if (at(i) == 0) {
            continue;
        }
        for (uint32_t j = i + 1; j < 16; j++) {
            if (at(j) != 0 && at(i) > at(j)) {
                inversion_count++;
            }
        }
    }
    int zero_row = this->zero_position / 4;
    return ((zero_row + inversion_count) % 2 != 0);
}

// Goal is "123456789ABCDEF0"
bool Puzzle::is_goal() {
    // quick check
    if (zero_position != 15) {
        return false;
    }
    // skip the last one (0)
    for (int i = 0; i < 15; i++) {
        if (at(i) != i + 1) {
            return false;
        }
    }
    return true;
}

int manhattan_distance(int i, int j) {
    int ix = i % 4, iy = i / 4;
    int jx = j % 4, jy = j / 4;
    return abs(ix - jx) + abs(iy - jy);
}

int Puzzle::heuristic() { return this->heuristic_v; }

int Puzzle::calculate_heuristic() {
    int val = 0;
    for (int i = 0; i < 16; i++) {
        uint8_t c = this->at(i);
        // does not include 0
        if (c != 0) {
            val += manhattan_distance(c - 1, i);
        }
    }
    return val;
}

int Puzzle::find_zero_position() {
    for (int i = 0; i < 16; i++) {
        if (this->at(i) == 0) {
            return i;
        }
    }
    return -1;
}

// returns false if the move is invalid
bool Puzzle::move(Direction dir) {
    int p0 = this->zero_position;
    int new_p0;

    switch (dir) {
    case UP:
        new_p0 = p0 + 4;
        if (new_p0 >= 16) {
            return false;
        }
        break;
    case DOWN:
        new_p0 = p0 - 4;
        if (new_p0 < 0) {
            return false;
        }
        break;
    case LEFT:
        new_p0 = p0 + 1;
        // not movable if zero is at the right most column
        if ((new_p0 >= 16) || (new_p0 % 4 == 0)) {
            return false;
        }
        break;
    case RIGHT:
        new_p0 = p0 - 1;
        // not movable if zero is at the left most column
        if ((new_p0 < 0) || ((new_p0 + 1) % 4 == 0)) {
            return false;
        }
        break;
    default:
        return false;
    }

    int tile = at(new_p0) - 1;
    this->heuristic_v -= manhattan_distance(tile, new_p0);
    this->swap(p0, new_p0);
    this->zero_position = new_p0;
    this->heuristic_v += manhattan_distance(tile, p0);

    return true;
}