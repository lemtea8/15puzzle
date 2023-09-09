#include "puzzle.hpp"
#include "hex.hpp"

Puzzle::Puzzle() { this->bits = 0; }

Puzzle::Puzzle(uint64_t bits) { this->bits = bits; }

// "0" stands for the blank
Puzzle::Puzzle(const std::string &input) {
    this->bits = 0;
    for (int i = 0; i < input.size(); i++) {
        char c = input[i];
        uint64_t num = hex_to_int(c);
        // each cell takes four bits (0~F)
        this->bits |= num << (i * 4);
    }
}

// // returns the element of xth row and yth column
// uint8_t Puzzle::at(int x, int y) {
//     int offset = (x * 4 + y) * 4;
//     uint64_t mask = uint64_t(0b1111) << offset;
//     return (Puzzle & mask) >> offset;
// }

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

bool Puzzle::solvable() {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (at(i) == 0) {
            count += (i + 1) / 4; // row of 0
            break;
        }
    }
    for (uint32_t i = 0; i < 16; i++) {
        if (at(i) == 0) {
            continue;
        }
        for (uint32_t j = i + 1; j < 16; j++) {
            if (at(j) != 0 && at(i) > at(j)) {
                count++;
            }
        }
    }
    return (count % 2 == 0);
}

// Goal is "123456789ABCDEF0"
bool Puzzle::is_goal() {
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

#include <iostream>

int Puzzle::heuristic() {
    int val = 0;
    for (int i = 0; i < 16; i++) {
        uint8_t c = this->at(i);
        // does not include 0
        if (c != 0) {
            // std::cout << int(c) << " " << i+1 << " " << manhattan_distance(c-1, i) << std::endl;;
            val += manhattan_distance(c-1, i);
        }
    }
    return val;
}

// if it's invalid, doesn't do anything
void Puzzle::move(Direction dir) {
    // find where is "0"
    int p0 = 0;
    for (int i = 0; i < 16; i++) {
        if (this->at(i) == 0) {
            p0 = i;
            break;
        }
    }

    switch (dir) {
    case UP:
        if (p0 + 4 < 16) {
            this->swap(p0, p0 + 4);
        }
        break;
    case DOWN:
        if (p0 - 4 >= 0) {
            this->swap(p0, p0 - 4);
        }
        break;
    case LEFT:
        if ((p0 + 1 < 16) && ((p0 + 1) % 4 != 0)) {
            this->swap(p0, p0 + 1);
        }
        break;
    case RIGHT:
        if ((p0 - 1 >= 0) && (p0 % 4 != 0)) {
            this->swap(p0, p0 - 1);
        }
        break;
    default:
        break;
    }
}