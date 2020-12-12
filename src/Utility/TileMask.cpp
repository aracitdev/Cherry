#include "TileMask.h"
#include <iostream>
#include <bitset>

Tilemask::Tilemask(uint8_t v)
{
    mask = v;
    wildcardMask = 0;
}

Tilemask::Tilemask()
{
}

Tilemask::Tilemask(const std::string& str)
{
    LoadFromString(str);
}

Tilemask::Tilemask(uint8_t m, uint8_t w)
{
    mask=m;
    wildcardMask=w;
}

void Tilemask::LoadFromString(const std::string& in)
{
    mask = 0;
    wildcardMask = 0;
    for(size_t i=0; i < in.size(); i++)
    {
        if(i != 5 &&  in[i] != '-')
        {
            switch(tolower(in[i]))
            {
            case '1':
                mask+=1;
                wildcardMask+=1;    //bit matters, so bit wildcard mask is 1
                break;
            case '0':
                wildcardMask+=1;    //bit matters. so bit in wildcard mask is 1
            break;
            }
            if(i != in.size()-1)
            {
                mask = mask << 1;
                wildcardMask = wildcardMask << 1;
            }
        }
    }
}

bool Tilemask::FitsMask(uint8_t v) const
{
    return !((v ^ mask) & wildcardMask);    //bitwise magic
}


bool Tilemask::operator<(const Tilemask& other) const
{
    return  mask < (other.mask & wildcardMask);
}

bool Tilemask::operator==(const Tilemask& other) const
{
    return FitsMask(other.mask);
}
