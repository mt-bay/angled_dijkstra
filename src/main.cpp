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
        dst.push_back(1627);

        cd::t_p_graph result_graph;
        
        cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");
        io::t_log::get_instance().write_line(std::to_string(graph.get_V_size()));

        io::t_log::get_instance().write_line("dijkstra start");
        di::t_dijkstra* dij  =
            new di::t_dijkstra(graph, src, false, 0);

        io::t_log::get_instance().write_line("dijkstra to p_graph");
        result_graph = dij->to_p_graph_part_of(dst);
        result_graph.to_csv("result\\cost0\\p_graph.csv");
            
        io::t_log::get_instance().write_line("dijkstra to JMC");
        jmc::t_JMC result_jmc = jmc::t_JMC(result_graph, src);

        io::t_log::get_instance().write_line("output JMC");
        result_jmc.output("result\\cost0\\JMC\\");

        delete dij;

        graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");

        io::t_log::get_instance().write_line("angled dijkstra start");
        dij =
            new di::t_angled_dijkstra
                (graph, src, 10000.0, 0.048, 0.080, false, 0);

        io::t_log::get_instance().write_line("angled dijkstra to p_graph");
        result_graph = dij->to_p_graph_part_of(dst);
        result_graph.to_csv("result\\cost10000\\p_graph.csv");

        io::t_log::get_instance().write_line("angled dijkstra to JMC");
        jmc::t_JMC result_a_jmc(result_graph, src);

        io::t_log::get_instance().write_line("output JMC");
        result_a_jmc.output("result\\cost10000\\JMC\\");

        delete dij;
    }
    catch(std::exception e)
    {
        io::t_log::get_instance().write_line("catch");
        io::t_log::get_instance().write_line(e.what());
        return 1;
    }

    return 0;
}