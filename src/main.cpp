

#include <iostream>
#include <string>

#include <cmath>

#include "tools/coordinate.hpp"
#include "tools/graph.hpp"

int main(int argc, char** argv){
    try
    {

        cd::t_graph test = cd::t_graph();
    }
    catch(...)
    {
        std::cout << "catch" << std::endl;
    }

    std::getchar();
    return 0;
}