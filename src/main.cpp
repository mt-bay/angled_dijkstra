#pragma warning(disable : 4290) //hide warning C4290


#include <iostream>
#include <string>
#include <vector>

#include "coordinate/coordinate.hpp"
#include "coordinate/graph.hpp"

#include "dijkstra/dijkstra.hpp"

int main(int argc, char** argv)
{
    std::vector< cd::t_xy<long int> > test_V
        = std::vector< cd::t_xy<long int> >(0, cd::t_xy<long int>(0, 0));

    test_V.push_back(cd::t_xy<long int>(0, 0));
    test_V.push_back(cd::t_xy<long int>(4, 0));
    test_V.push_back(cd::t_xy<long int>(0, 4));
    test_V.push_back(cd::t_xy<long int>(4, 4));
    test_V.push_back(cd::t_xy<long int>(15, 15));

    std::vector< std::vector<unsigned char> > test_adj
        = std::vector< std::vector<unsigned char> >
            (5, std::vector<unsigned char>(5, true));

    try
    {
        cd::t_graph test = cd::t_graph(test_V, test_adj);

        test.to_csv("test graph.csv");
        
        di::t_dijkstra test_dij
            = di::t_dijkstra::gen_dijkstra_angled(test, 0.0, 0, false, 0);
        test_dij.to_csv("test.csv");
    }
    catch(std::exception e)
    {
        std::cout << "catch" << std::endl;
        std::cout << e.what() << std::endl;
    }

    return 0;
}