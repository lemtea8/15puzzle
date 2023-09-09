#include "hex.hpp"

int hex_to_int(char c) {
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

char int_to_hex(int i) {
    if (i < 10) {
        return i + '0';
    }
    return 'A' + i - 10;
}
