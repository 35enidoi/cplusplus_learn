#ifndef REVERSI_H
#define REVERSI_H

#include <vector>
#include <utility>
#include <array>
#include <string>

struct ReversiPos {
    unsigned char x_size;
    unsigned char y_size;
    unsigned char x;
    unsigned char y;

    ReversiPos();

    ReversiPos(unsigned char _x_size, unsigned char _y_size, unsigned char _x, unsigned char _y);

    std::pair<unsigned char, unsigned char> size() const noexcept;

    std::pair<unsigned char, unsigned char> pos() const noexcept;

    int to_num() const noexcept;

    std::string visualize() const noexcept;
};

class Reversi {
private:
    const std::array<std::pair<int, int>, 8> ROTATE = {
        std::make_pair(-1, 1), {0, 1}, {1, 1},
                      {-1, 0},         {1, 0},
                      {-1, -1},{0, -1}, {1, -1}
    };
    unsigned char x = 0;
    unsigned char y = 0;
    std::vector<bool> valid_spaces{};
    std::vector<bool> white_stones{};
    std::vector<bool> black_stones{};
    std::vector<ReversiPos> white_valid_positions{};
    std::vector<ReversiPos> black_valid_positions{};

    void reverse_stone(ReversiPos a);

    int set_stone_topos(int _x, int _y) const noexcept;

    bool stone_x_pos_is_valid(int _x) const noexcept;

    bool stone_y_pos_is_valid(int _y) const noexcept;

    std::vector<ReversiPos> get_stone_num(unsigned char x_, unsigned char y_, bool color) const;

    void put_stone(ReversiPos a, bool color);

    void stone_valid_all_check();

public:
    const bool WHITE = false;
    const bool BLACK = true;

    const std::vector<ReversiPos> &black_valid_pos = black_valid_positions;
    const std::vector<ReversiPos> &white_valid_pos = white_valid_positions;

    explicit Reversi(const unsigned char x_size, const unsigned char y_size);

    void resize(const unsigned char x_size, const unsigned char y_size);

    void set_stone(ReversiPos a, bool color);

    ReversiPos create_reversipos(unsigned char _x, unsigned char _y) const;

    ReversiPos create_reversipos_fromint(unsigned int a) const;

    std::string visualize() const noexcept;
};

#endif // REVERSI_H
