#pragma once

#include <tchar.h>
#include <xstring>

#include "coordinate/coordinate.hpp"


const cd::t_xy<int> window_size = cd::t_xy<int>(1000, 1000);

typedef TCHAR tchar;
typedef std::basic_string<tchar> tstring;