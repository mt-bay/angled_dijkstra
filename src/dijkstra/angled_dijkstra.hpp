#pragma once

#include "dijkstra.hpp"

namespace di
{


class t_angled_dijkstra : public t_dijkstra
{
public :
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
    t_angled_dijkstra
        (const cd::t_p_graph _graph          ,
         const unsigned int  _src_node_number,
         const long double   _angle_weight   ,
         const double        _accident_left  ,
         const double        _accident_right ,
         const bool          _use_dst
                                = false      ,
         const unsigned int  _dst_node_number
                                = 0          )
            throw(::std::out_of_range);

    /*
     * destructor
     */
    virtual ~t_angled_dijkstra();

    /* operator overload */
public    :
    virtual t_angled_dijkstra& operator= (const t_angled_dijkstra& _rhs);

    /* method */
public:
    /* 
     * get route cost information
     * parameter    : index
     * return value : route cost information
     */
    virtual std::string get_route_cost_information(unsigned int _index);

protected:
    /* 
     * run angled dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number,
     *                angle weight(angle cost : |weight * sin(angle / 2)|),
     *                use destination node
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    virtual void run_dijkstra
        (const bool           _use_dst
                                = false       ,
         const unsigned int   _dst_node_number
                                = 0           )
            throw(std::out_of_range);

    

    /* 
     * initilize instance
     * parameter    : graph size, source node number
     * return value : void
     * exception    : std::out_of_range
     */
    inline void init(const cd::t_p_graph& _graph          ,
                     const unsigned int   _src_node_number,
                     const long double    _angle_wight    ,
                     const double         _accident_left  ,
                     const double         _accident_right )
                        throw(std::out_of_range);

    /* 
     * copy constractor
     * parameter    : origin
     * return value : deep copy
     * return value : void
     * exception    : none
     */
    inline void deep_copy(const t_angled_dijkstra& _origin);

    /* member variable and instance */
public:
    std::vector<long double> m_sum_angle_cost;
protected:
    long double              m_angle_weight;
    double                   m_accident_left;
    double                   m_accident_right;
};


}