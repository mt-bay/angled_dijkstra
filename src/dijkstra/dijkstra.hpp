/* 
 * 
 */

#ifndef SRC_DIJKSTRA_DIJKSTRA_H
#define SRC_DIJKSTRA_DIJKSTRA_H

#include <iostream>
#include <vector>
#include <functional>

namespace cd{
class graph;
}

namespace di{
/* class */
/* 
 * class which run dijkstra and recording resalt
 */
class t_dijkstra{
    /* member valiable and instance */
public:
    unsigned int                              m_src_node_number;
    std::vector<long double>*                 m_route_cost;
    std::vector< std::vector<unsigned int> >* m_path;

    /* constractor, destractor */
public:
    /* 
     * default constractor
     * parameter : void
     * built     : empty
     * exception : none
     */
    t_dijkstra();

    /* 
     * copy constractor
     * parameter : origin
     * built     : deep copy
     * exception : none
     */
    t_dijkstra(const t_dijkstra& _origin);

    /* 
     * size setter constracter
     * parameter : size of graph, source node number
     * built     : initialized dijkstra result
     * exception : std::out_of_range
     */
    t_dijkstra(const unsigned int _size           ,
               const unsigned int _src_node_number)
                  throw(std::out_of_range);

protected:

    /* method */
public:
    /* 
     * run nomal dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    static t_dijkstra gen_dijkstra(cd::graph    _graph          , 
                                   unsigned int _src_node_number,
                                   unsigned int _dst_node_number)
                                       throw(std::out_of_range);

    /* 
     * run angled dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number,
     *                angle cost(lambda fomula)
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    static t_dijkstra gen_dijkstra_angled(cd::graph _graph                 ,
                                          unsigned int _src_node_number    ,
                                          unsigned int _dst_node_number    ,
                                          std::function<double> _andle_cost)
                                              throw(std::out_of_range);

protected:
    /* 
     * seting size of graph
     * parameter    : graph size
     * return value : void
     * exception    : none
     */
    inline void set_graph_size(unsigned int _graph_size);

    /* 
     * initilize instance
     * parameter    : graph size, source node number
     * return value : void
     * exception    : std::out_of_range
     */
    inline void init(const unsigned int _graph_size     ,
                     const unsigned int _src_node_number)
                  throw(std::out_of_range);
};

}

#endif  //SRC_DIJKSTRA_DIJKSTRA_H