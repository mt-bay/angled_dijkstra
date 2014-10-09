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
    try
    {
        cd::t_graph test
            = cd::t_graph::csv_location_and_csv_adj_to_graph
                ("bin\\test_loc.csv",
                 "bin\\test_adj.csv"     );

        test.to_csv("test graph.csv", false);

        di::t_dijkstra::gen_dijkstra(test, 0U, false, 0)
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