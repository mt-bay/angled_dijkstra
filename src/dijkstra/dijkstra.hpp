/* 
 * 
 */

#ifndef SRC_DIJKSTRA_DIJKSTRA_H
#define SRC_DIJKSTRA_DIJKSTRA_H

#include <iostream>
#include <vector>
#include <functional>

namespace cd
{
class t_graph;
}

namespace di
{
/* class */
/* 
 * class which run dijkstra and recording resalt
 */
class t_dijkstra
{
    /* member valiable and instance */
public    :
    cd::t_graph*                              m_graph;
protected :
    unsigned int                              m_src_node_number;
    std::vector<long double>*                 m_route_cost;
    std::vector<unsigned char>*               m_is_confirmed;
    std::vector< std::vector<unsigned int> >* m_path;

    /* constractor, destractor */
public    :
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
    t_dijkstra(const cd::t_graph   _graph          ,
               const unsigned int  _src_node_number)
                  throw(::std::out_of_range);

protected :

    /* method */
public    :
    /* 
     * graph size getter
     * parameter    : void
     * return value : network size
     * exception    : none
     */
    unsigned int get_V_size() const;

    /* 
     * run nomal dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    static t_dijkstra gen_dijkstra(const cd::t_graph  _graph          , 
                                   const unsigned int _src_node_number,
                                   const unsigned int _dst_node_number,
                                   const bool         _use_dst = true )
                                       throw(::std::out_of_range);

    /* 
     * run angled dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number,
     *                angle weight(angle cost : |weight * sin(angle / 2)|),
     *                use destination node
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    static t_dijkstra gen_dijkstra_angled(const cd::t_graph  _graph          ,
                                          const unsigned int _src_node_number,
                                          const unsigned int _dst_node_number,
                                          const long double  _angle_weight   ,
                                          const bool         _use_dst = true )
                                              throw(std::out_of_range);


protected :
    /* 
     * get angle cost
     * parameter    : angle weight, source node number, destination node number
     * return value : angle cost
     * exception    : out_of_range
     */
   inline  double get_angle_cost(const double       _angle_cost     ,
                                 const unsigned int _src_node_number,
                                 const unsigned int _dst_node_number);

    /* 
     * path to angle
     * parameter    : source node number, destination node number
     * return value : angle that path of A to B
     * exception    : out_of_range
     */
    double     path_to_angle(unsigned int _src_node_number,
                             unsigned int _dst_node_number)
                                 throw(std::out_of_range);

    /* 
     * check to satisfy end condition
     * parameter    : use destination node, destination node number
     * return value : satisfy end condition
     * exception    : none
     */
    bool satisfy_end_condition(const bool         _use_dst = false    ,
                               const unsigned int _dst_node_number = 0);

    /* 
     * get confirm node number
     * parameter    : void
     * return value : confirm node number
     * exception    : none
     */
    unsigned int get_confirm_node_number();

    /* 
     * seting size of graph
     * parameter    : graph size
     * return value : void
     * exception    : none
     */
    inline void set_graph_size(const unsigned int _graph_size);

    /* 
     * initilize instance
     * parameter    : graph size, source node number
     * return value : void
     * exception    : std::out_of_range
     */
    inline void init(const cd::t_graph  _graph          ,
                     const unsigned int _src_node_number)
                        throw(std::out_of_range);

    /* 
     * copy constractor
     * parameter    : origin
     * return value : deep copy
     * return value : void
     * exception    : none
     */
    inline void deep_copy(const t_dijkstra& _origin);
};

}

#endif  //SRC_DIJKSTRA_DIJKSTRA_H