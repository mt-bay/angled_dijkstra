#pragma warning(disable : 4290) //hide warning C4290


#include <iostream>
#include <string>
#include <vector>

#include "coordinate/coordinate.hpp"
#include "coordinate/graph.hpp"

#include "dijkstra/dijkstra.hpp"
#include "dijkstra/angled_dijkstra.hpp"

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
        cd::t_graph test
            = cd::t_graph::csv_location_and_csv_adj_to_graph
                ("bin\\test_location.csv",
                 "bin\\test_adj.csv"     );

        std::cout << test.m_node_location << std::endl;
        std::cout << test.get_V_size() <<std::endl;

        test.to_csv("test graph.csv", false);

        di::t_dijkstra::gen_dijkstra(test, 0)
            .to_csv("test(cost0).csv");

        di::t_angled_dijkstra::gen_dijkstra(test, 50.0, 0)
            .to_csv("test(cost50).csv");
    }
    catch(std::exception e)
    {
        std::cout << "catch" << std::endl;
        std::cout << e.what() << std::endl;
        std::getchar();
    }

    return 0;
}