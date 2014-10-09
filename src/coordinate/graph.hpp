#pragma once

#pragma warning(disable : 4290) //hide warning C4290

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

class t_graph
{
    /* constractor, destractor */
public    :
    /* 
     * default constructor
     * parameter : void
     * build     : empty network
     * exception : none
     */
    t_graph();

    /* 
     * copy constructor
     * parameter : original
     * build     : deep copy
     * exception : none
     */
    t_graph(const t_graph& _origin);

    /* 
     * setter constructor(no location)
     * parameter : E
     * build     : network by parameter
     * exception : none
     */
    t_graph(const std::vector< std::vector<long double  > > _link_cost       ,
            const std::vector< std::vector<unsigned char> > _adjacency_matrix);

    /* 
     * setter constructor
     * parameter : V's location,@adjacency matrix
     * build     : network by parameter
     * exception : none
     */
    t_graph(const std::vector< t_xy<int> >                  _node_location   ,
            const std::vector< std::vector<unsigned char> > _adjacency_matrix);

    /* 
     * destructor
     * parameter : void
     */
    virtual ~t_graph();


    /* static method */
public    :
    /* 
     * csv(link cost) to graph
     * "-"          -> INFINITY,
     * double value -> link cost
     * parameter    : csv file path
     * return value : graph
     * exception    : none
     */
    static t_graph csv_link_cost_to_graph(std::string _file_path);

    /* 
     * csv(location) and csv(adjacency matrix) to graph
     * parameter    : csv file(location), csv file(adjacency matrix)
     * return value : graph
     * exception    : none
     */
    static t_graph csv_location_and_csv_adj_to_graph
                (std::string _file_path_location,
                 std::string _file_path_adj     );

    /* 
     * jmc map data to graph
     * parameter    : jmc data file directory
     * return value : graph
     * exception    : none
     */
    static t_graph jmc_to_graph(std::string _jmc_data_dir);

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

    /* 
     * this instance to csv
     * parameter    : file path, write index
     * return value : write successful
     * exception    : none
     */
    bool to_csv(std::string _file_path, bool _write_index = true);

protected :
    /* 
     * add size of graph
     * parameter    : size to add
     * return value : void
     * exception    : none
     */
    virtual void add_graph_size(unsigned int _add_graph_size);

    /* 
     * seting size of graph
     * parameter    : graph size
     * return value : void
     * exception    : none
     */
    virtual void set_graph_size(unsigned int _graph_size);

    /* 
     * setting node location
     * parameter    : node number  , location (single)
                      node location, write flag(array)
     * return value : void
     * exception    : out_of_range
     */
    inline virtual void set_node_location(const unsigned int   _node_number  ,
                                          const t_xy<int>      _node_location) 
                                             throw(::std::out_of_range);
    inline virtual void set_node_location(const std::vector<t_xy<int> >
                                                    _node_location_array  ,
                                          const std::vector<unsigned char>
                                                    _do_write             )
                                              throw(std::out_of_range);


    /* const value and instance */


    /* static valiable and instance */


    /* member variable and instance */
public    :
    //V
    std::vector< t_xy<int>* >*                 m_node_location;

protected :
    //E
    std::vector< std::vector<unsigned char> >* m_adjacency_matrix;
    std::vector< std::vector<long double> >*   m_link_cost;
private   :
    
};

}
