#include "reversi/algorithms.hpp"

#include "reversi/util.hpp"
#include "reversi/exception.hpp"

ReversiPos ReversiAlgorithms::RandomSelect::select(std::vector<ReversiPos> positions) {
    return ReversiAlgorithms::RandomSelect::static_select(positions);
}

ReversiPos ReversiAlgorithms::RandomSelect::static_select(std::vector<ReversiPos> positions) {
    if (positions.size() == 0) {
        throw ReversiException::AlgorithmSelectNoStone();
    } else {
        unsigned int select_pos = ReversiUtil::randint(0, positions.size() - 1);
        return positions.at(select_pos);
    }
}
