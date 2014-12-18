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
    int arg_index = 0;

    double angle_cost
        = (argc > (++arg_index))? std::stod(argv[arg_index]) : 0.0;

    io::t_log::get_instance().write_line("angle cost     : " + std::to_string(angle_cost));

    double accident_left
        = (argc > (++arg_index))? std::stod(argv[arg_index]) : 1.0;

    io::t_log::get_instance().write_line("accident left  : " + std::to_string(accident_left));

    double accident_right
        = (argc > (++arg_index))? std::stod(argv[arg_index]) : 1.0;

    io::t_log::get_instance().write_line("accident right : " + std::to_string(accident_right));

    unsigned int src
        =  (argc > (++arg_index))? std::stoi(argv[arg_index]) : 0;

    io::t_log::get_instance().write_line("src. node num. : " + std::to_string(src));

    std::vector<unsigned int> dst;

    if(argc <= (++arg_index))
    {
        dst.push_back(0);
    }
    for(true ; arg_index < argc; ++arg_index)
    {
        dst.push_back(std::stoi(argv[arg_index]));
    }


    io::t_log::get_instance().write     ("dst. node num. : ");
    for(size_t s = 0; s < dst.size(); ++s)
    {
        io::t_log::get_instance().write(std::to_string(dst.at(s)) + ", ");
    }
    io::t_log::get_instance().write_line();
    
    try
    {
        io::t_log::get_instance().write_line("graph load");

        cd::t_p_graph result_graph;

        result_graph = cd::t_p_graph::csv_to_graph("result\\common\\p_graph.csv");
        
        /*
        cd::t_p_graph graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");
        io::t_log::get_instance().write_line
            (std::to_string(graph.get_V_size()));

        io::t_log::get_instance().write_line("dijkstra start");
        di::t_dijkstra dij  =
            di::t_dijkstra(graph, src, false, 0);

        io::t_log::get_instance().write_line("dijkstra to p_graph");
        result_graph = dij.to_p_graph_part_of(dst);
        result_graph.to_csv("result\\common\\p_graph.csv");  
        */

        io::t_log::get_instance().write_line("dijkstra to JMC");
        jmc::t_JMC result_jmc = jmc::t_JMC(result_graph, src);
        
        io::t_log::get_instance().write_line("output JMC");
        result_jmc.output("result\\common\\JMC\\");

        /*
        graph
            = cd::t_p_graph::csv_to_graph("bin\\p_graph.csv");

        io::t_log::get_instance().write_line("angled dijkstra start");
        di::t_angled_dijkstra a_dij =
            di::t_angled_dijkstra
                (graph, src, angle_cost, accident_left, accident_right, false, 0);

        io::t_log::get_instance().write_line("angled dijkstra to p_graph");
        cd::t_p_graph result_a_graph = a_dij.to_p_graph_part_of(dst);
        result_a_graph.to_csv("result\\angled\\p_graph.csv");

        io::t_log::get_instance().write_line("angled dijkstra to JMC");
        jmc::t_JMC result_a_jmc = jmc::t_JMC(result_a_graph, src);

        io::t_log::get_instance().write_line("output JMC");
        result_a_jmc.output("result\\angled\\JMC\\");
        */
    }
    catch(std::exception e)
    {
        io::t_log::get_instance().write_line("catch");
        io::t_log::get_instance().write_line(e.what());
        return 1;
    }

    return 0;
}