#include "reversi/reversi.hpp"
#include "reversi/util.hpp"

#include <iostream>


int main() {
    unsigned int n = 0;
    while (true) {
        Reversi a{8, 8};

        n += 1;

        while (!a.is_finish()) {
            auto valid_stones = (a.NEXT ? a.black_valid_pos : a.white_valid_pos);
            auto hoge = ReversiUtil::randint(0, valid_stones.size());
            auto stone_pos = valid_stones.at(hoge);
        
            a.set_stone(stone_pos, a.NEXT);
        }

        if (a.MOVECOUNT !=60) {
            std::cout << a.visualize() << std::endl;
            std::cout << "Movecount: " << a.MOVECOUNT << std::endl;
            std::cout << "Total generate: " << n << std::endl;
            break;
        }
    }
}
