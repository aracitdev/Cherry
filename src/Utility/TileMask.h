#ifndef TILEMASK_H_INCLUDED
#define TILEMASK_H_INCLUDED
#include <cstdint>
#include <string>

class Tilemask
{
public:

    Tilemask(uint8_t v);
    Tilemask();
    Tilemask(const std::string&);
    Tilemask(uint8_t m, uint8_t w);

    bool operator<(const Tilemask& other) const;
    bool operator==(const Tilemask& other) const;

    void LoadFromString(const std::string& in);
    bool FitsMask(uint8_t v) const;

    uint8_t mask;   //mask (wildcard bits do not matter on value)
    uint8_t wildcardMask;    //wildcard bits set to zero
private:

};

#endif // TILEMASK_H_INCLUDED
