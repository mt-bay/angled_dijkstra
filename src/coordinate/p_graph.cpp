#include <fstream>
#include <list>

#include "p_graph.hpp"

#include "coordinate.hpp"

#include "../log/log.hpp"

#include "../tools/tools.hpp"

namespace cd
{
t_p_graph::t_p_graph()
{
    init();
}


t_p_graph::t_p_graph(const t_p_graph& _origin)
    : t_p_graph()
{
    for(std::vector< cd::t_xy<int>* >::iterator it
            = _origin.m_node_location->begin();
        it != _origin.m_node_location->end();
        ++it)
    {
        m_node_location->push_back(new cd::t_xy<int>(**it));
    }

    for(unsigned int i = 0; i < _origin.m_adjacency->size(); ++i)
    {
        m_adjacency->push_back(std::vector<unsigned int>());
        for(unsigned int j = 0; j < _origin.m_adjacency->at(i).size(); ++j)
        {
            m_adjacency->at(i).push_back(_origin.m_adjacency->at(i).at(j));
        }
    }

    for(unsigned int i = 0; i < _origin.m_link_cost->size(); ++i)
    {
        m_link_cost->push_back(std::vector<long double>());
        for(unsigned int j = 0; j < _origin.m_link_cost->at(i).size(); ++j)
        {
            m_link_cost->at(i).push_back(_origin.m_link_cost->at(i).at(j));
        }
    }
}


t_p_graph& t_p_graph::csv_link_cost_to_graph(std::string _file)
{
    t_p_graph result = t_p_graph();

    mt::mkdir(_file);
    std::ifstream csv = std::ifstream(_file);

    if(csv.fail())
    {
        io::t_log::get_instance().write_line("csv read failed");
        throw std::exception("csv read failed");
    }

    std::string line;
    std::vector<std::string> elm;

    while(std::getline(csv, line))
    {
        elm = mt::split_v(line, ",");
        result.m_node_location->push_back(new cd::t_xy<int>
                                                (std::stoi(elm.at(0)),
                                                 std::stoi(elm.at(1))));
        result.m_adjacency->push_back(std::vector<unsigned int>());
        for(unsigned int i = 2; i < elm.size(); ++i)
        {
            result.m_adjacency->at(result.m_adjacency->size() - 1)
                .push_back(std::stoi(elm.at(i)));
        }
    }
    csv.close();

    for(unsigned int i = 0; i < result.m_node_location->size(); ++i)
    {
        result.m_link_cost->push_back(std::vector<long double>());
        for(unsigned int j = 0; j < result.m_adjacency->at(i).size(); ++j)
        {
            result.m_link_cost->at(i).push_back
                (cd::t_xy<int>::length(*result.m_node_location->at(i),
                                       *result.m_node_location->at(j)));
        }
    }

    return result;
}


unsigned int t_p_graph::get_V_size()
    const
{
    return m_node_location->size();
}


long double t_p_graph::get_link_cost(const unsigned int _src_node_num, 
                                     const unsigned int _dst_node_num)
    const
{
    for(unsigned int i = 0; i < m_adjacency->at(_src_node_num).size(); ++i)
    {
        if(m_adjacency->at(_src_node_num).at(i) == _dst_node_num)
        {
            return m_link_cost->at(_src_node_num).at(i);
        }
    }
    return (long double)INFINITY;
}


unsigned char t_p_graph::get_adjacency(const unsigned int _src_node_num,
                                       const unsigned int _dst_node_num)
    const
{
    for(unsigned int i = 0; i < m_adjacency->at(_src_node_num).size(); ++i)
    {
        if(m_adjacency->at(_src_node_num).at(i) == _dst_node_num)
        {
            return (unsigned char)1;
        }
    }
    return (unsigned char)0;
}


void t_p_graph::init()
{
    m_node_location = new std::vector< cd::t_xy<int>* >();

    m_adjacency = new std::vector< std::vector<unsigned int> >();
    m_link_cost = new std::vector< std::vector<long double> >();
}

}