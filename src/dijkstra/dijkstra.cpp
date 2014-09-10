#include "dijkstra.hpp"
#include "../tools/graph.hpp"
#include "../tools/coordinate.hpp"

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

t_dijkstra::t_dijkstra(unsigned int _graph_size,
                       unsigned int _src_node_number)
                          throw(std::out_of_range)
{
    init(_graph_size, _src_node_number);
}

/* method */
t_dijkstra t_dijkstra::gen_dijkstra(cd::graph    _graph          , 
                                    unsigned int _src_node_number,
                                    unsigned int _dst_node_number)
                                        throw(std::out_of_range)
{
    std::function<double> lambda = [](cd::t_xy<int> _p0,
                                      cd::t_xy<int> _p1,
                                      cd::t_xy<int> _p2)
                                      {
                                          0.0;
                                      };
    gen_dijkstra_angled(_graph, 0, 0, lambda);
}

t_dijkstra t_dijkstra::gen_dijkstra_angled(cd::graph _graph                 ,
                                           unsigned int _src_node_number    ,
                                           unsigned int _dst_node_number    ,
                                           std::function<double> _andle_cost)
                                               throw(std::out_of_range)
{
    //preprcessing
    if(_src_node_number <                   0 ||
       _src_node_number >= _graph.get_V_size())
       throw;
    if(_dst_node_number <                   0 ||
       _dst_node_number >= _graph.get_V_size())
       throw;
    std::function<double> cost = (_andle_cost != nullptr)?
                                     std::function<double>(_andle_cost) :
                                     std::function<double>(        0.0) ;

    //
    

}

void t_dijkstra::set_graph_size(unsigned int _graph_size)
{
    m_route_cost = & std::vector<long double>(_graph_size, 0.0);
    m_path       = &std::vector< std::vector<unsigned int> >
                       (_graph_size, std::vector<unsigned int>
                                         (0, 0));
}

inline void t_dijkstra::init(unsigned int _graph_size     ,
                             unsigned int _src_node_number)
                                throw(std::out_of_range)
{
    if(_src_node_number >= _graph_size)
        throw;

    m_route_cost      = &std::vector<long double>(_graph_size,
                                                  (long double)INFINITY);
    m_src_node_number = _src_node_number;
    m_route_cost->at(_src_node_number) = 0.0;
    
    m_path            = &std::vector< std::vector<unsigned int> >
                          (_graph_size, std::vector<unsigned int>());
}
}