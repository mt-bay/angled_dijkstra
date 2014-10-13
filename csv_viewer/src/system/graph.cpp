#include "graph.hpp"

#include <iostream>
#include <fstream>

#include "../define.hpp"
#include "../coordinate/coordinate.hpp"
#include "../log/log.hpp"
#include "../tools/tools.hpp"


namespace sys
{
t_graph::t_graph()
{
    ErrorLogAdd(_T("graph construct"));
    
    m_location = new std::vector< cd::t_xy<int>* >();
    m_adjacency_matrix = new std::vector< std::vector<unsigned char> >
                            (0, std::vector<unsigned char>());
}

t_graph::t_graph(std::string _location_csv_path ,
                 std::string _adjacency_csv_path)
{
    ErrorLogAdd(_T("graph construct\n"));

    m_location = new std::vector< cd::t_xy<int>* >();
    m_adjacency_matrix = new std::vector< std::vector<unsigned char> >
                            (0, std::vector<unsigned char>());

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
                ((unsigned char)std::stoi(elm.at(j)));
        }
    }
    csv_adj.close();
}

void t_graph::show_mesh_grid(int _color)
{
    ErrorLogAdd(_T("show grid\n"));
    const int SECONDARY_MESH_SIZE = 10000;
    cd::t_xy<int> lowerleft  = get_lower_left();
    cd::t_xy<int> upperright = get_upper_right();
    cd::t_xy<int> draw_point;

    //draw parallel line
    for(int i = lowerleft.x; i <= upperright.x; i += SECONDARY_MESH_SIZE)
    {
        draw_point = get_draw_point(cd::t_xy<int>(i, lowerleft.y));
        DrawLine(draw_point.x, 0, draw_point.x, window_size.y, _color);
    }
    //draw parallel line
    for(int i = lowerleft.y; i <= upperright.y; i += SECONDARY_MESH_SIZE)
    {
        draw_point = get_draw_point(cd::t_xy<int>(lowerleft.x, i));
        DrawLine(0, draw_point.y, window_size.x, draw_point.y, _color);
    }
}

void t_graph::show_line(int _color)
{
    ErrorLogAdd(_T("show line\n"));
    cd::t_xy<int> p_src;
    cd::t_xy<int> p_dst;

    for(unsigned int i = 0; i < m_adjacency_matrix->size(); ++i)
    {
        p_src = get_draw_point(*m_location->at(i));

        for(unsigned int j = 0; j < m_adjacency_matrix->at(i).size(); ++j)
        {
            if(m_adjacency_matrix->at(i).at(j))
            {
                p_dst = get_draw_point(*m_location->at(j));
                DrawLine(p_src.x, p_src.y, p_dst.x + 2, p_dst.y + 2, _color);
            }
        }
    }
    //draw point
    

    return;
}

void t_graph::show_point(int _color)
{
    cd::t_xy<int> p_src;
    for(unsigned int i = 0; i < m_adjacency_matrix->size(); ++i)
    {
        p_src = get_draw_point(*m_location->at(i));
        DrawBox(p_src.x - 1, p_src.y - 1, p_src.x + 2, p_src.y + 2, _color, TRUE);
    }
}


cd::t_xy<int> t_graph::get_draw_point(cd::t_xy<int> _src_location)
{
    cd::t_xy<int> lower_left  = get_lower_left();
    cd::t_xy<int> upper_right = get_upper_right();

    int width  = upper_right.x - lower_left.x;
    int height = upper_right.y - lower_left.y;

    return cd::t_xy<int>(
            (int)(((double)(_src_location.x - lower_left.x) / (double)(width))
            * window_size.x)                                                  ,
            (int)((1.0
             - ((double)(_src_location.y - lower_left.y) / (double)(height)))
            * window_size.y));
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