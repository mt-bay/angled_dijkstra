#pragma warning(disable : 4290) //hide warning C4290

#include <iostream>
#include <string>

#include <vector>

#include "tools/coordinate.hpp"
#include "tools/graph.hpp"

int main(int argc, char** argv){
    std::vector< cd::t_xy<long int> > test_V = std::vector< cd::t_xy<long int> >(0, cd::t_xy<long int>(0, 0));

    test_V.push_back(cd::t_xy<long int>(0, 0));
    test_V.push_back(cd::t_xy<long int>(4, 0));
    test_V.push_back(cd::t_xy<long int>(0, 4));
    test_V.push_back(cd::t_xy<long int>(4, 4));
    test_V.push_back(cd::t_xy<long int>(15, 15));

    for(unsigned int i = 0; i < test_V.size(); ++i)
    {
        std::cout << "test_V[" << i << "] = " << test_V.at(i).toString() << std::endl;
    }

    std::vector< std::vector<unsigned char> > test_adj
        = std::vector< std::vector<unsigned char> >(5, std::vector<unsigned char>(5, true));

    try
    {
        cd::t_graph test = cd::t_graph(test_V, test_adj);
    }
    catch(std::exception e)
    {
        std::cout << "catch" << std::endl;
        std::cout << e.what() << std::endl;
    }

    std::getchar();
    return 0;
}