#include "reversi.hpp"
#include "exception.hpp"

// structure

// ReversiPos

ReversiPos::ReversiPos(unsigned char _x_size, unsigned char _y_size, unsigned char _x, unsigned char _y)
    : x_size(_x_size), y_size(_y_size), x(_x), y(_y) {}

std::pair<unsigned char, unsigned char> ReversiPos::size() {
    return std::make_pair(x_size, y_size);
}

std::pair<unsigned char, unsigned char> ReversiPos::pos() {
    return std::make_pair(x, y);
}

int ReversiPos::to_num() {
    return x + (y * x_size);
}

// class

// Reversi

// public

void Reversi::set_size(unsigned char _x, unsigned char _y) {
    x = _x;
    y = _y;
}

bool Reversi::is_valid(ReversiPos a) {
    return valid_spaces[a.to_num()];
}

ReversiPos Reversi::create_reversipos(unsigned char _x, unsigned char _y) {
    if (x < _x) {
        throw SizeOver(false, x, _x);
    } else if (y < _y) {
        throw SizeOver(true, y, _y);
    }
    return ReversiPos(x, y, _x, _y);
}
