#ifndef SRC_TOOLS_GRAPH_H_
#define SRC_TOOLS_GRAPH_H_

#include <iostream>
#include <vector>

#include "coordinate.hpp"

template <typename T>
class xy_t<T>;

namespace ad{

class graph{
    /* member variable and instance */
public:
    //V
    std::vector< cd::xy_t<long int>* >*        node_location;
    //E
    std::vector< std::vector<unsigned char> >* adjacency_matrix;
    std::vector< std::vector<long double> >*   link_cost;
private:
    
    /* constractor, destractor */
public:
    /* 
     * default constractor
     * parameter : void
     * build     : empty network
     * exception : none
     */
    graph();

    /* 
     * copy constractor
     * parametor : original
     * build     : copy
     * exception : none
     */
    graph(const graph& _origin);

    /* method */
public:
    /* 
     * get |V|
     * parameter    : void
     * return value : |V|
     * exception    : none
     */
    unsigned int get_V_size();

    /* 
     * get link cost
     * parameter    : source node number, destination node number
     * return value : link cost
     * exception    : none
     */
    long double get_link_cost(unsigned int _src_node_num, 
                              unsigned int _dst_node_num);

    /* 
     * set link cost
     * parameter    : link cost, source node number, destination node number
     * return value : void
     * exception    : out_of_range
     */
    void set_link_cost(long     double  _link_cost   ,
                       unsigned int     _src_node_num,
                       unsigned int     _dst_node_num)
                           throw(std::out_of_range);


protected:
    /* 
     * 
     * parameter    : graph size
     * return value : void
     * side effect  : seting size of graph
     * exception    : none
     */
    virtual void set_graph_size(unsigned int _graph_size);
};

}

#endif //SRC_TOOLS_GRAPH_H_