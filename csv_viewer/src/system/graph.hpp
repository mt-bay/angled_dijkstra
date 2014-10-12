#pragma once


#include <string>
#include <vector>

#include "DxLib.h"


namespace cd
{
template<typename T>
class t_xy;
}


namespace sys
{

class t_graph
{
    /* constructor */
public :
    /* 
     * default constructor
     * parameter : void
     * build     : empty network
     * exception : none
     */
    t_graph();


    /* 
     * csv reader constructor
     * parameter : csv file path(location, adj.)
     * build     : graph based on csv
     * exception : none
     */
    t_graph(std::string _location_csv_path ,
            std::string _adjacency_csv_path);
private:


    /* method */
public :
    /* 
     * show secondary mesh grid
     * parameter    : void
     * return value : void
     * exception    : none
     */
    void show_mesh_grid(int _color);
    /* 
     * show this graph line
     * parameter    : void
     * return value : void
     * exception    : none
     */
    void show_line(int _color);

    /* 
     * show this graph point
     * parameter    : void
     * return value : void
     * exception    : none
     */
    void show_point(int _color);
private:
    /* 
     * get draw point
     * parameter    : source location
     * return value : draw point
     * exception    : none
     */
    cd::t_xy<int> get_draw_point(cd::t_xy<int> _src_location);


    /* 
     * get graph lower-left
     * parameter    : void
     * return value : lower-left
     * exception    : none
     */
    cd::t_xy<int> get_lower_left();

    /* 
     * get graph upper-right
     * parameter    : void
     * return value : upper-right
     * exception    : none
     */
    cd::t_xy<int> get_upper_right();

    /* member variable and instance */
public :
    std::vector< cd::t_xy<int>* >*             m_location;
    std::vector< std::vector<unsigned char> >* m_adjacency_matrix;

private:


};

}