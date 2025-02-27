#include "exception.hpp"

// SizeOver

SizeOver::SizeOver(const bool& x_or_y, const unsigned char& _limit, const unsigned char& _over) : x_y(x_or_y), limit(_limit), over(_over) {}

const char* SizeOver::what() const noexcept{
    std::string text = (x_y ? 'x' : 'y') + " size overed. size: " + std::to_string(limit) + " over: " + std::to_string(over);
    return text.c_str();
}
