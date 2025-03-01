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

// private

void Reversi::set_stone(ReversiPos a ,bool color) {
    // todo
}

// public

void Reversi::init_set_size(unsigned char _x, unsigned char _y) {
    x = _x;
    y = _y;
    valid_spaces.clear();
    for (int i; i <= y; i++) {
        for (int r; r <= x; r++) {
            valid_spaces.push_back(true);
        }
    }
}

void Reversi::init_stone() {
    if (x > 4 and y > 4) {
        int x_center = x / 2;
        int y_center = y / 2;

        ReversiPos hidariue(x, y, x_center, y_center), migiue(x, y, x_center+1, y_center), hidarisita(x, y, x_center, y_center+1), migisita(x, y, x_center+1, y_center+1);
        set_stone(hidariue, WHITE);
        set_stone(migiue, BLACK);
        set_stone(hidarisita, BLACK);
        set_stone(migisita, WHITE);
    }
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
