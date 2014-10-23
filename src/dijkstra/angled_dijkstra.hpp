#pragma once


#include "dijkstra.hpp"

namespace di
{
class t_angled_dijkstra : public t_dijkstra
{
    /* constructor and destractor */
public    :
    /* 
     * default constractor
     * parameter : void
     * built     : empty
     * exception : none
     */
    t_angled_dijkstra();

    /* 
     * copy constractor
     * parameter : origin
     * built     : deep copy
     * exception : none
     */
    t_angled_dijkstra(const t_angled_dijkstra& _origin);

    /* 
     * size setter constructor
     * parameter : size of graph, source node number
     * built     : initialized dijkstra result
     * exception : std::out_of_range
     */
    t_angled_dijkstra(cd::t_graph*        _graph          ,
                      const unsigned int  _src_node_number)
                        throw(::std::out_of_range);
protected :
private   :

    /* operator overload */
public    :
protected :
private   :

    /* static method */
public    :
    /* 
     * run angled dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number,
     *                angle weight(angle cost : |weight * sin(angle / 2)|),
     *                use destination node
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    static t_angled_dijkstra gen_dijkstra(cd::t_graph*       _graph          ,
                                          const long double  _angle_weight   ,
                                          const unsigned int _src_node_number,
                                          const bool         _use_dst
                                                                = false      ,
                                          const unsigned int _dst_node_number
                                                                = 0          )
                                            throw(std::out_of_range);
    
protected :
private   :


    /* method */
public    :
protected :
    /* 
     * get angle cost
     * parameter    : angle weight, source node number, destination node number
     * return value : angle cost
     * exception    : out_of_range
     */
    inline double get_angle_cost(const double       _angle_cost     ,
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
private   :


    /* member const value and instance */
public    :
protected :
private   :


    /* static variable and instance */
public    :
protected :
private   :


    /* member variable and instance */
public    :
protected :
private   :

};
}