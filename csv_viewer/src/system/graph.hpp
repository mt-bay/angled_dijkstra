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
     * show this graph
     * parameter    : void
     * return value : void
     * exception    : none
     */
    void show();
private:
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