#ifndef REVERSI_H
#define REVERSI_H

#include <vector>
#include <limits>
#include <utility>
#include <array>

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
    const std::array<std::pair<int, int>, 8> ROTATE = {
        std::make_pair(-1, 1), {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {-1, -1}
    };
    unsigned char x = 0;
    unsigned char y = 0;
    std::vector<bool> valid_spaces{};
    std::vector<bool> white_stones{};
    std::vector<bool> black_stones{};

private:
    void set_stone(ReversiPos a, bool color);

public:
    const bool WHITE = false;
    const bool BLACK = true;

    void init_set_size(unsigned char _x, unsigned char _y);

    void init_stone();

    bool is_valid(ReversiPos a);

    ReversiPos create_reversipos(unsigned char _x, unsigned char _y);
};

#endif // REVERSI_H
