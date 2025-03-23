#include "reversi/exception.hpp"

ReversiException::BaseReversiException::BaseReversiException(const std::string &msg)
: std::runtime_error(msg) {};

ReversiException::SizeOver::SizeOver(bool x_y, int limit, int over)
: BaseReversiException(std::string(x_y ? "y" : "x") + " limit exceeded.  limit: " + std::to_string(limit) + ", size: " + std::to_string(over)) {};

ReversiException::SetStoneInvalidPos::SetStoneInvalidPos(unsigned int x, unsigned int y)
: BaseReversiException("Stone has already placed. place: (" + std::to_string(x) + "x" + std::to_string(y) + ")") {};

ReversiException::SetStoneColorNotMatch::SetStoneColorNotMatch(bool next, bool color)
: BaseReversiException("wrong stone color. next: " + std::string((next ? "BLACK" : "WHITE")) + ", color: " + (color ? "BLACK" : "WHITE")) {};
