#include "dijkstra.hpp"
#include "../tools/graph.hpp"

namespace di{
/* constractor and destractor */
t_dijkstra::t_dijkstra()
{
}

    /* 
     * copy constractor
     * parameter : origin
     * built     : deep copy
     * exception : none
     */
t_dijkstra::t_dijkstra(const t_dijkstra& _origin)
{

}

/* method */
t_dijkstra t_dijkstra::gen_dijkstra(cd::graph    _graph          , 
                                    unsigned int _src_node_number,
                                    unsigned int _dst_node_number)
                                        throw(std::out_of_range)
{
}

t_dijkstra t_dijkstra::gen_dijkstra_angled(cd::graph _graph                ,
                                           unsigned int _src_node_number   ,
                                           unsigned int _dst_node_number   ,
                                           std::function<double> andle_cost)
{
}

void t_dijkstra::set_graph_size(unsigned int _graph_size)
{
    m_route_cost = & std::vector<long double>(_graph_size, 0.0);
    m_path       = &std::vector< std::vector<unsigned int> >
                       (_graph_size, std::vector<unsigned int>
                                         (0, 0));
}

void t_dijkstra::init(unsigned int _graph_size, unsigned int _src_node_number)
                  throw(std::out_of_range)
{

}
}