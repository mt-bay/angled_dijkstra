#pragma warning(disable : 4290) //hide warning C4290


#include <iostream>
#include <string>
#include <vector>

#include "coordinate/coordinate.hpp"
#include "coordinate/p_graph.hpp"

#include "JMC/JMC.hpp"

#include "dijkstra/dijkstra.hpp"
#include "dijkstra/angled_dijkstra.hpp"

#include "log/log.hpp"

int main(int argc, char** argv)
{
    try
    {
        const unsigned int src = 0;
        
        std::vector<unsigned int> write_dst;

        io::t_log::get_instance().write_line("graph load");
        cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");

        write_dst.push_back(100); write_dst.push_back(1000);
        
        {
            cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");

            io::t_log::get_instance().write_line("dijkstra start");
            di::t_dijkstra dij_cost0  =
                di::t_dijkstra::gen_dijkstra(graph, src, false, 0);
            
            io::t_log::get_instance().write_line("dijkstra to JMC");
            jmc::t_JMC jmc_cost0 = jmc::t_JMC(dij_cost0);
            jmc_cost0.output("result\\cost0\\JMC\\");
        }

        {
            cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");

            io::t_log::get_instance().write_line("angled dijkstra start");
            di::t_dijkstra dij_cost100 =
                di::t_dijkstra::gen_a_dijkstra(graph, 100.0, src, false, 0);

            io::t_log::get_instance().write_line("angled dijkstra to JMC");
            jmc::t_JMC jmc_cost100 = jmc::t_JMC(dij_cost100);
            jmc_cost100.output("result\\cost100\\JMC\\");
        }
        
    }
    catch(std::exception e)
    {
        io::t_log::get_instance().write_line("catch");
        io::t_log::get_instance().write_line(e.what());
        return 1;
    }

    return 0;
}