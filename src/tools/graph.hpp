#ifndef SRC_TOOLS_GRAPH_H_
#define SRC_TOOLS_GRAPH_H_

#include <iostream>
#include <vector>

//#include "coordinate.hpp"

namespace cd
{
template<typename T>
class t_xy;

}


namespace cd
{

class t_graph
{
    /* member variable and instance */
public    :
    //V
    std::vector< t_xy<long int>* >*            m_node_location;

protected :
    //E
    std::vector< ::std::vector<unsigned char> >* m_adjacency_matrix;
    std::vector< ::std::vector<long double> >*   m_link_cost;
private   :
    
    /* constractor, destractor */
public    :
    /* 
     * default constractor
     * parameter : void
     * build     : empty network
     * exception : none
     */
    t_graph();

    /* 
     * copy constractor
     * parameter : original
     * build     : deep copy
     * exception : none
     */
    t_graph(const t_graph& _origin);

    /* 
     * setter constractor(no location)
     * parameter : E
     * build     : network by parameter
     * exception : none
     */
    t_graph(const std::vector< std::vector<long double  > > _link_cost       ,
            const std::vector< std::vector<unsigned char> > _adjacency_matrix);

    /* 
     * setter constractor
     * parameter : V's location,Å@adjacency matrix
     * build     : network by parameter
     * exception : none
     */
    t_graph(const std::vector< t_xy<long int> >             _node_location   ,
            const std::vector< std::vector<unsigned char> > _adjacency_matrix);

    /* 
     * destractor
     * parameter : void
     */
    ~t_graph();

    /* method */
public    :
    /* 
     * get |V|
     * parameter    : void
     * return value : |V|
     * exception    : none
     */
    unsigned int get_V_size() const;

    /* 
     * get link cost
     * parameter    : source node number, destination node number
     * return value : link cost
     * exception    : none
     */
    long double get_link_cost(unsigned int _src_node_num, 
                              unsigned int _dst_node_num) const;

    /* 
     * set link cost
     * parameter    : link cost, source node number, destination node number
     * return value : void
     * exception    : out_of_range
     */
    void set_link_cost(long     double _link_cost   ,
                       unsigned int    _src_node_num,
                       unsigned int    _dst_node_num)
                           throw(std::out_of_range);


protected :
    /* 
     * seting size of graph
     * parameter    : graph size
     * return value : void
     * exception    : none
     */
    inline virtual void set_graph_size(unsigned int _graph_size);

    /* 
     * setting node location
     * parameter    : node number  , location (single)
                      node location, write flag(array)
     * return value : void
     * exception    : out_of_range
     */
    inline virtual void set_node_location(const unsigned int   _node_number  ,
                                          const t_xy<long int> _node_location) 
                                             throw(::std::out_of_range);
    inline virtual void set_node_location(const std::vector<t_xy<long int> >
                                                    _node_location_array    ,
                                          const std::vector<unsigned char  >
                                                    _do_write               )
                                              throw(std::out_of_range);
};

}

#endif //SRC_TOOLS_GRAPH_H_