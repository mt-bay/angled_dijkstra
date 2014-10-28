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
        
        io::t_log::get_instance().write_line("graph load");

        std::vector<unsigned int> dst;
        //dst.push_back(4);
        dst.push_back(1627);

        cd::t_p_graph result_graph;
        
        {
            cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");
            io::t_log::get_instance().write_line(std::to_string(graph.get_V_size()));

            io::t_log::get_instance().write_line("dijkstra start");
            di::t_dijkstra dij_cost0  =
                di::t_dijkstra::gen_dijkstra(graph, src, false, 0);
            
            io::t_log::get_instance().write_line("dijkstra to p_graph");
            //result_graph = dij_cost0.to_p_graph();
            result_graph = dij_cost0.to_p_graph_part_of(dst);
            result_graph.to_csv("result\\cost0\\p_graph.csv");
            
            io::t_log::get_instance().write_line("dijkstra to JMC");
            jmc::t_JMC jmc_cost0 = jmc::t_JMC(result_graph, src);
            jmc_cost0.output("result\\cost0\\JMC\\");
            
        }

        {
            cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");

            io::t_log::get_instance().write_line("angled dijkstra start");
            di::t_dijkstra dij_cost1000 =
                di::t_dijkstra::gen_a_dijkstra(graph, 1000.0, src, false, 0);

            io::t_log::get_instance().write_line("angled dijkstra to p_graph");
            //result_graph = dij_cost1000.to_p_graph();
            result_graph = dij_cost1000.to_p_graph_part_of(dst);
            result_graph.to_csv("result\\cost1000\\p_graph.csv");
            
            io::t_log::get_instance().write_line("angled dijkstra to JMC");
            jmc::t_JMC jmc_cost1000 = jmc::t_JMC(result_graph, src);
            jmc_cost1000.output("result\\cost1000\\JMC\\");
            
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