#include "graph.hpp"

#include <iostream>

#include "../coordinate/coordinate.hpp"

namespace sys
{
t_graph::t_graph()
{
    m_location = new std::vector< cd::t_xy<int>* >();
    m_adjacency_matrix = new std::vector< std::vector<unsigned char> >
                            (0, std::vector<unsigned char>());
}

t_graph::t_graph(std::string location_csv_path ,
                 std::string adjacency_csv_path)
{

}

}