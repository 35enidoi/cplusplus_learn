#include "reversi.hpp"
#include "exception.hpp"

// structure

// ReversiPos

ReversiPos::ReversiPos() : x_size(0), y_size(0), x(0), y(0) {};

ReversiPos::ReversiPos(unsigned char _x_size, unsigned char _y_size, unsigned char _x, unsigned char _y)
    : x_size(_x_size), y_size(_y_size), x(_x), y(_y) {
    if (_x_size <= _x)
    {
        throw ReversiException::SizeOver(false, _x_size, _x);
        } else if (_y_size <= _y) {
            throw ReversiException::SizeOver(true, y_size, _y);
        }
    }

std::pair<unsigned char, unsigned char> ReversiPos::size() {
    return std::make_pair(x_size, y_size);
}

std::pair<unsigned char, unsigned char> ReversiPos::pos() {
    return std::make_pair(x, y);
}

int ReversiPos::to_num() {
    return x + (y * x_size);
}

std::string ReversiPos::visualize() const {
    std::string return_string = "size: " + std::to_string(x_size) + "x" + std::to_string(y_size) + "\n";
    return_string += "pos: " + std::to_string(x) + "x" + std::to_string(y) + "\n";

    for (int _y = 0; _y < y_size; _y++)
    {
        for (int _x = 0; _x < x_size; _x++)
        {
            if (_x == x && _y == y)
            {
                return_string += "+";
            } else {
                return_string += "-";
            }

        }

        return_string += "\n";
    }

    return return_string;
}

// class

// Reversi

// private

void Reversi::reverse_stone(ReversiPos a) {
    if (black_stones.at(a.to_num())) {
        black_stones[a.to_num()] = false;
        white_stones[a.to_num()] = true;
    } else if (white_stones.at(a.to_num())) {
        white_stones[a.to_num()] = false;
        black_stones[a.to_num()] = true;
    }
}

int Reversi::set_stone_topos(int _x, int _y) const noexcept {
    return x * _y + _x;
}

bool Reversi::stone_x_pos_is_valid(int _x) const noexcept {
    return 0 <= _x && _x < x;
}

bool Reversi::stone_y_pos_is_valid(int _y) const noexcept {
    return 0 <= _y && _y < y;
}

std::vector<ReversiPos> Reversi::get_stone_num(unsigned char _x, unsigned char _y, bool color) const {
    std::vector<bool> enemy_stones = color ? white_stones : black_stones;
    std::vector<bool> own_stones = color ? black_stones : white_stones;

    std::vector<ReversiPos> return_heap{};
    std::vector<ReversiPos> return_positions{};

    int i = 1;
    int x_pos = 0;
    int y_pos = 0;
    for (const auto& [x_rotate, y_rotate] : ROTATE) {
        i = 1;
        return_heap.clear();
        while (true) {
            x_pos = _x + x_rotate * i;
            y_pos = _y + y_rotate * i;
            if (!stone_x_pos_is_valid(x_pos) or !stone_y_pos_is_valid(y_pos)) {
                // 石の場所が不正の時
                break;
            } else if (!enemy_stones.at(set_stone_topos(x_pos, y_pos))) {
                // 石の場所が敵の石ではないとき
                if (return_heap.size() > 0 && own_stones.at(set_stone_topos(x_pos, y_pos))) {
                    // 石の場所が自分の石であり、heap内に石があるとき。
                    return_positions.insert(return_positions.end(), return_heap.begin(), return_heap.end()); // 合成
                }
                break;
            } else {
                // 石の場所が適正で敵の石の時
                return_heap.push_back(create_reversipos(x_pos, y_pos));
            }

            i++;
        }
    }

    return return_positions;
}

void Reversi::put_stone(ReversiPos a, bool color) {
    valid_spaces[a.to_num()] = false;
    (color ? black_stones : white_stones)[a.to_num()] = true;
}

void Reversi::stone_valid_all_check() {
    white_valid_positions.clear();
    black_valid_positions.clear();

    ReversiPos pos{};
    for (unsigned int i = 0; i < valid_spaces.size(); i++) {
        pos = create_reversipos_fromint(i);
        if (valid_spaces[i]) {
            if (get_stone_num(pos.x, pos.y, WHITE).size() > 0) {
                white_valid_positions.push_back(pos);
            } else if (get_stone_num(pos.x, pos.y, BLACK).size() > 0) {
                black_valid_positions.push_back(pos);
            }
        }
    }
}

// public

Reversi::Reversi(const unsigned char &x_size, const unsigned char &y_size) {
    resize(x_size, y_size);
}

void Reversi::resize(const unsigned char x_size, const unsigned char y_size) {
    x = x_size;
    y = y_size;
    valid_spaces.clear();
    valid_spaces.resize(y * x, true);
    black_stones.clear();
    black_stones.resize(y * x, false);
    white_stones.clear();
    white_stones.resize(y * x, false);
    black_valid_positions.clear();
    white_valid_positions.clear();

    if (x >= 4 and y >= 4) {
        int x_center = (x / 2) - 1;
        int y_center = (y / 2) - 1;

        ReversiPos
            hidariue = create_reversipos(x_center, y_center),
            migiue = create_reversipos(x_center + 1, y_center),
            hidarisita = create_reversipos(x_center, y_center + 1),
            migisita = create_reversipos(x_center + 1, y_center + 1);

        put_stone(hidariue, WHITE);
        put_stone(migiue, BLACK);
        put_stone(hidarisita, BLACK);
        put_stone(migisita, WHITE);

        stone_valid_all_check();
    }
}

void Reversi::set_stone(ReversiPos a ,bool color) {
    if (!valid_spaces[a.to_num()]) {
        throw ReversiException::SetStoneInvalidPos(a.x, a.y);
    }
    put_stone(a, color);

    auto [_x, _y] = a.pos();

    for (const ReversiPos revpos : get_stone_num(_x, _y, color)) {
        reverse_stone(revpos);
    }

    stone_valid_all_check();
}

ReversiPos Reversi::create_reversipos(unsigned char _x, unsigned char _y) const {
    return ReversiPos(x, y, _x, _y);
}

ReversiPos Reversi::create_reversipos_fromint(unsigned int a) const {
    unsigned char _x = a % y;
    unsigned char _y = a / y;
    return create_reversipos(_x, _y);
}

std::string Reversi::visualize() const {
    std::string return_string = "black: b, white: w\n";
    for (unsigned int i = 0; i < valid_spaces.size(); i++) {
        if (valid_spaces.at(i)) {
            return_string += "-";
        } else {
            if (black_stones.at(i)) {
                return_string += "b";
            } else if (white_stones.at(i)) {
                return_string += "w";
            }
        }

        if (i != 0 && ((i + 1)%x == 0)) {
            return_string += "\n";
        }
    }

    return return_string;
}
