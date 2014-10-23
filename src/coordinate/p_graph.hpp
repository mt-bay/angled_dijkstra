#pragma once

#pragma warning(disable : 4290) //hide warning C4290
#pragma warning(disable : 4267) //hide warning C4267

#include <iostream>
#include <string>
#include <vector>


namespace cd
{
template<typename T>
class t_xy;

}


namespace cd
{

class t_p_graph
{
    /* constractor, destractor */
public    :
    /* 
     * default constructor
     * parameter : void
     * build     : empty network
     * exception : none
     */
    t_p_graph();

    /* 
     * size setter constructor
     * parameter : size of graph
     * build     : sizd empty network
     * exception : none
     */
    t_p_graph(const unsigned int _size);

    /* 
     * copy constructor
     * parameter : original
     * build     : deep copy
     * exception : none
     */
    t_p_graph(const t_p_graph& _origin);

    /* 
     * setter constructor
     * parameter : V's location,@adjacency matrix
     * build     : network by parameter
     * exception : none
     */
    t_p_graph(const std::vector< t_xy<int> >                 _node_location,
              const std::vector< std::vector<unsigned int> > _adjacency    );

    /* 
     * destructor
     * parameter : void
     */
    virtual ~t_p_graph();


    /* static method */
public    :
    /* 
     * csv(p_graph) to graph
     * parameter    : csv file path
     * return value : graph
     * exception    : none
     */
    static t_p_graph& csv_link_cost_to_graph(std::string _file);


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
    long double get_link_cost(const unsigned int _src_node_num, 
                              const unsigned int _dst_node_num) const;

    /* 
     * get adjacency
     * parameter    : source node number, destination node number
     * return value : adjacency
     * exception    : none
     */
    unsigned char get_adjacency(const unsigned int _src_node_num,
                                const unsigned int _dst_node_num) const;

protected :
    /* 
     * add size of graph
     * parameter    : size to add
     * return value : void
     * exception    : none
     */
    virtual void add_graph_size(unsigned int _add_graph_size);

    /* 
     * init graph
     * parameter    : void
     * return value : void
     * exception    : none
     */
    inline virtual void init();
    

    /* const value and instance */


    /* static valiable and instance */


    /* member variable and instance */
public    :
    std::vector< t_xy<int>* >*                m_node_location;

protected :
    std::vector< std::vector<unsigned int> >* m_adjacency;
    std::vector< std::vector<long double> >*  m_link_cost;
private   :
    
};

}
