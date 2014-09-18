#include <iostream>

namespace jmc
{

enum layer_code : int
{
    ADMINISTRATIVE = 1,
    COASTLINE      = 1,
    ROAD           = 2,
    TRACK          = 3,
    RIVER          = 5,
    LAKE           = 5
};

struct header
{
    layer_code code;
    unsigned int 
};

}