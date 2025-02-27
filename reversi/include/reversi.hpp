#ifndef REVERSI_H
#define REVERSI_H

#include <vector>
#include <limits>
#include <utility>

struct ReversiPos {
    unsigned char x_size;
    unsigned char y_size;
    unsigned char x;
    unsigned char y;

    ReversiPos(unsigned char _x_size, unsigned char _y_size, unsigned char _x, unsigned char _y);

    std::pair<unsigned char, unsigned char> size();

    std::pair<unsigned char, unsigned char> pos();

    int to_num();
};

class Reversi {
private:
    const bool white = false;
    const bool black = true;
    unsigned char x = 0;
    unsigned char y = 0;
    std::vector<bool> valid_spaces{};
    std::vector<bool> black_stones{};

public:
    void set_size(unsigned char _x, unsigned char _y);

    bool is_valid(ReversiPos a);

    ReversiPos create_reversipos(unsigned char _x, unsigned char _y);
};

#endif // REVERSI_H
