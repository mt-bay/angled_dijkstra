#pragma once


#pragma warning(disable : 4290) //hide warning C4290

#include <iostream>
#include <string>
#include <vector>
#include <exception>


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
     * size setter constructor
     * parameter : size of graph, source node number
     * built     : initialized dijkstra result
     * exception : std::out_of_range
     */
    t_dijkstra(cd::t_graph*        _graph          ,
               const unsigned int  _src_node_number)
                  throw(::std::out_of_range);

    /* 
     * destructor
     */
    virtual ~t_dijkstra();
protected :
private   :

    /* operator overload */
public    :
    virtual t_dijkstra& operator= (t_dijkstra& _rhs);
protected :
private   :

    /* static method */
public    :
    /* 
     * run dijkstra
     * parameter    : network graph, 
     *                source node number, destination node number
     * return value : dijkstra result
     * exception    : std::out_of_range
     */
    static t_dijkstra gen_dijkstra(cd::t_graph*       _graph          , 
                                   const unsigned int _src_node_number,
                                   const bool         _use_dst 
                                                        = false       ,
                                   const unsigned int _dst_node_number
                                                        = 0           )
                                    throw(::std::out_of_range);

    
protected :
private   :

    /* method */
public    :
    /* 
     * graph size getter
     * parameter    : void
     * return value : network size
     * exception    : none
     */
    virtual unsigned int get_V_size() const;

    /* 
     * this instance to csv file
     * parameter    : file name
     * return value : write successful
     * exception    : none
     */
    virtual bool to_csv(const std::string _file_path) const;

    /* 
     * this instance to graph
     * parameter    : void
     * return value : converted graph
     * exception    : none
     */
    virtual cd::t_graph to_graph() const;

    virtual cd::t_graph to_graph_part_of(const std::vector<unsigned int>& _dst)
                                            const;

protected :
    /* 
     * copy constractor
     * parameter    : origin
     * return value : deep copy
     * return value : void
     * exception    : none
     */
    virtual inline void deep_copy(const t_dijkstra& _origin);

    /* 
     * find secondary mesh is
     * parameter    : search file path
     * return value : to add line number(if found)
     *                -1(if not fund)
     * exception    : none
     */
    virtual int find_secondary_mesh_is(std::ofstream* _search_file_ofs) const;
    
    /* 
     * get confirm node number
     * parameter    : void
     * return value : confirm node number
     * exception    : none
     */
    virtual unsigned int get_confirm_node_number() const;

    /* 
     * initilize instance
     * parameter    : graph size, source node number
     * return value : void
     * exception    : std::out_of_range
     */
    virtual inline void init(cd::t_graph*       _graph          ,
                             const unsigned int _src_node_number)
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
     * seting size of graph
     * parameter    : graph size
     * return value : void
     * exception    : none
     */
    virtual inline void set_graph_size(const unsigned int _graph_size);
private   :

    /* const value and instance */
public    :
protected :
private   :

    /* static valiable and instance */


    /* member valiable and instance */
public    :
    cd::t_graph*                              m_graph;
    unsigned int                              m_src_node_number;
    std::vector<long double>*                 m_route_cost;
    std::vector<unsigned char>*               m_is_confirmed;
    std::vector< std::vector<unsigned int> >* m_path;
protected :
private   :
};

}