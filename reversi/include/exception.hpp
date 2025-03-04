#ifndef REVERSI_EXCEPTION_H
#define REVERSI_EXCEPTION_H


#include <stdexcept>

namespace ReversiException {
    class BaseReversiException : public std::runtime_error {
    public:
        BaseReversiException(const std::string& msg);
    };

    class SizeOver : public BaseReversiException {
    public:
        SizeOver(bool x_y, int limit, int over);
    };

    class SetStoneInvalidPos : public BaseReversiException {
    public:
        SetStoneInvalidPos(unsigned int x, unsigned int y);
    };
}

#endif // REVERSI_EXCEPTION_H
