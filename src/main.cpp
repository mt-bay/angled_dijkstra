#include <iostream>
#include <string>

#include "tools\coordinate.hpp"

int main(int argc, char** argv){
    try
    {
        cd::xy_t<int> hoge = cd::xy_t<int>(5, 5);
        std::cout << hoge.toString() << std::endl;
    }
    catch(...)
    {
        std::cout << "catch" << std::endl;
    }

    std::getchar();
    return 0;
}