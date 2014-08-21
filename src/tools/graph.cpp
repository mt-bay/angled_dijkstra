#include "graph.hpp"
#include "coordinate.hpp"

namespace ad
{
/* constractor and destractor */
graph::graph()
{
    set_graph_size(0);
}
graph::graph(const graph& _origin)
{

}


/* method */
unsigned int graph::get_V_size(){
    return adjacency_matrix->size();
}

long double graph::get_link_cost(unsigned int _src_node_num, 
                                 unsigned int _dst_node_num)
{
    try
    {
        if(adjacency_matrix->at(_src_node_num).at(_dst_node_num) == false)
            return static_cast<long double>(INFINITY);

        return link_cost->at(_src_node_num).at(_dst_node_num);
    }
    catch(std::out_of_range e)
    {
        return static_cast<long double>(INFINITY);
    }
}

void graph::set_link_cost(long     double  _link_cost   ,
                          unsigned int     _src_node_num,
                          unsigned int     _dst_node_num)
                              throw(std::out_of_range)
{
    if(_link_cost <  0                     ||
       _link_cost == (long double) INFINITY)
    {
        adjacency_matrix->at(_src_node_num).at(_dst_node_num)
            = false;
        link_cost->at(_src_node_num).at(_dst_node_num)
            = (long double) INFINITY;
        return;
    }



}

void graph::set_graph_size(unsigned int _graph_size)
{
    node_location    = &std::vector<cd::xy_t<long int>* >
                           (_graph_size, &cd::xy_t<long int>(0, 0));

    adjacency_matrix = &std::vector< std::vector<unsigned char> >
                            (_graph_size, std::vector<unsigned char>
                                              (_graph_size, false));

    link_cost        = &std::vector< std::vector<long double> >
                            (_graph_size, std::vector<long double>
                                              (_graph_size, 
                                               (long double)INFINITY));
}

}