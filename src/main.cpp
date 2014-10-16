#pragma warning(disable : 4290) //hide warning C4290


#include <iostream>
#include <string>
#include <vector>

#include "coordinate/coordinate.hpp"
#include "coordinate/graph.hpp"

#include "dijkstra/dijkstra.hpp"
#include "dijkstra/angled_dijkstra.hpp"

#include "log/log.hpp"

int main(int argc, char** argv)
{
    try
    {
        const unsigned int src = 0;

        cd::t_graph test
            = cd::t_graph::csv_location_and_csv_adj_to_graph
                ("bin\\location.csv",
                 "bin\\adj.csv"     );

        test.to_csv("test graph.csv", false);

        di::t_dijkstra dij_cost0  =
            di::t_dijkstra::gen_dijkstra(test, src, false, 0);
        dij_cost0.to_csv("result\\dij_cost0.csv");
        dij_cost0.to_graph().to_csv("result\\graph_cost0.csv");

        di::t_dijkstra dij_cost50 =
        di::t_angled_dijkstra::gen_dijkstra(test, 50.0, src);
        dij_cost50.to_csv("result\\dij_cost50.csv");
        dij_cost50.to_graph().to_csv("result\\graph_cost50.csv");

    }
    catch(std::exception e)
    {
        io::t_log::get_instance().write_line("catch");
        io::t_log::get_instance().write_line(e.what());
        return 1;
    }

    return 0;
}