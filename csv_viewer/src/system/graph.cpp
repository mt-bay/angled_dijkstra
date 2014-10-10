#include "graph.hpp"

#include <iostream>
#include <fstream>

#include "../coordinate/coordinate.hpp"
#include "../log/log.hpp"
#include "../tools/tools.hpp"


namespace sys
{
t_graph::t_graph()
{
    m_location = new std::vector< cd::t_xy<int>* >();
    m_adjacency_matrix = new std::vector< std::vector<unsigned char> >
                            (0, std::vector<unsigned char>());
}

t_graph::t_graph(std::string _location_csv_path ,
                 std::string _adjacency_csv_path)
{
    std::ifstream csv_location = std::ifstream(_location_csv_path);
    std::ifstream csv_adj      = std::ifstream(_adjacency_csv_path);

    if(csv_location.fail() || csv_adj.fail())
    {
        io::t_log::get_instance().write_line("csv read failed");
        throw std::exception("csv read failed");
    }

    std::string line;
    std::vector<std::string> elm;

    //get location data
    while(std::getline(csv_location, line))
    {
        elm = mt::split_v(line, ",");
        m_location->push_back(new cd::t_xy<int>(std::stoi(elm[0]),
                                                std::stoi(elm[1])));
    }
    csv_location.close();

    //get adj. matrix
    for(unsigned int i = 0;std::getline(csv_adj, line); ++i)
    {
        elm = mt::split_v(line, ",");
        m_adjacency_matrix->push_back(std::vector<unsigned char>(0, false));
        for(unsigned int j = 0; j < elm.size(); ++j)
        {
            m_adjacency_matrix->at(i).push_back
                ((unsigned char)std::stoi(elm.at(i)));
        }
    }
    csv_adj.close();
}


void t_graph::show()
{
    cd::t_xy<int> lower_left  = get_lower_left();
    cd::t_xy<int> upper_right = get_upper_right();

    cd::t_xy<int> p_src;
    cd::t_xy<int> p_dst;

    for(unsigned int i = 0; i < m_adjacency_matrix->size(); ++i)
    {
        p_src = cd::t_xy<int>((m_location->at(i)->x - lower_left.x))

        for(unsigned int j = 0; j < m_adjacency_matrix->at(i).size(); ++j)
        {
            if(m_adjacency_matrix->at(i).at(j))
            {

            }
        }
    }
}


cd::t_xy<int> t_graph::get_lower_left()
{
    cd::t_xy<int> result = cd::t_xy<int>(INT_MAX, INT_MAX);
    for(unsigned int i = 0; i < m_location->size(); ++i)
    {
        if(m_location->at(i)->x < result.x)
        {
            result.x = m_location->at(i)->x;
        }
        if(m_location->at(i)->y < result.y)
        {
            result.y = m_location->at(i)->y;
        }
    }
    return result;
}


cd::t_xy<int> t_graph::get_upper_right()
{
    cd::t_xy<int> result = cd::t_xy<int>(INT_MIN, INT_MIN);
    for(unsigned int i = 0; i < m_location->size(); ++i)
    {
        if(m_location->at(i)->x > result.x)
        {
            result.x = m_location->at(i)->x;
        }
        if(m_location->at(i)->y > result.y)
        {
            result.y = m_location->at(i)->y;
        }
    }
    return result;
}


}