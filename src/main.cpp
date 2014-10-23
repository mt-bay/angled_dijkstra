#pragma warning(disable : 4290) //hide warning C4290


#include <iostream>
#include <string>
#include <vector>

#include "coordinate/coordinate.hpp"
#include "coordinate/graph.hpp"

#include "JMC/JMC.hpp"

#include "dijkstra/dijkstra.hpp"
#include "dijkstra/angled_dijkstra.hpp"

#include "log/log.hpp"

int main(int argc, char** argv)
{
    try
    {
        const unsigned int src = 0;

        io::t_log::get_instance().write_line("graph load");
        cd::t_graph test
            = cd::t_graph::csv_location_and_csv_adj_to_graph
                ("bin\\location.csv",
                 "bin\\adj.csv"     );
        /*
        std::vector<unsigned int> write_dst;
        write_dst.push_back(100); write_dst.push_back(1000);
        {
            io::t_log::get_instance().write_line("dijkstra start");
            di::t_dijkstra dij_cost0  =
                di::t_dijkstra::gen_dijkstra(test, src, false, 0);
            
            io::t_log::get_instance().write_line("dijkstra to JMC");
            jmc::t_JMC jmc_cost0 = jmc::t_JMC(dij_cost0);
            jmc_cost0.output("result\\cost100\\JMC\\");
        }
        {
            io::t_log::get_instance().write_line("angled dijkstra start");
            di::t_dijkstra dij_cost100 =
                di::t_angled_dijkstra::gen_dijkstra(test, 100.0, src);

            io::t_log::get_instance().write_line("angled dijkstra to JMC");
            jmc::t_JMC jmc_cost100 = jmc::t_JMC(dij_cost100);
            jmc_cost100.output("result\\cost100\\JMC\\");
        }
        */
    }
    catch(std::exception e)
    {
        io::t_log::get_instance().write_line("catch");
        io::t_log::get_instance().write_line(e.what());
        return 1;
    }
    std::cout << "wait key" <<std::endl;
    std::getchar();
    return 0;
}