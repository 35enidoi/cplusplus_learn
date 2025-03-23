#ifndef REVERSI_ALGORITHMS_H
#define REVERSI_ALGORITHMS_H

#include <vector>

#include "reversi/reversi.hpp"
#include "reversi/util.hpp"
#include "reversi/exception.hpp"

namespace ReversiAlgorithms {
    class ABCReversiAlgorithms {
    public:
        virtual ReversiPos select(std::vector<ReversiPos> positions) = 0;
    };

    class RandomSelect : public ABCReversiAlgorithms {
    public:
        ReversiPos select(std::vector<ReversiPos> positions);

        static ReversiPos static_select(std::vector<ReversiPos> positions);
    };
}

#endif // REVERSI_ALGORITHMS_H
