#include "reversi/util.hpp"

int ReversiUtil::randint(int under_limit, int over_limit) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> random_generate(under_limit, over_limit - 1);
    return random_generate(gen);
}
