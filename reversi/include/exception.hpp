#ifndef REVERSI_EXCEPTION_H
#define REVERSI_EXCEPTION_H

#include <stdexcept>

class SizeOver : public std::exception {
private:
    bool x_y;
    unsigned char limit;
    unsigned char over;
public:
    explicit SizeOver(const bool& _color, const unsigned char& _limit, const unsigned char& _over);

    const char* what() const noexcept override;
};

#endif
