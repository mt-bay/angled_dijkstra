#include "graph.hpp"
#include "coordinate.hpp"
#include "../log/log.hpp"

namespace cd
{
/* constractor and destractor */
t_graph::t_graph()
{
    set_graph_size(1);
}
t_graph::t_graph(const t_graph& _origin)
{
    set_graph_size(_origin.get_V_size());
    for(unsigned int i = 0; i < _origin.get_V_size(); i++)
    {
        m_node_location->at(i) = _origin.m_node_location->at(i);
        for(unsigned int j = 0; j < _origin.get_V_size(); j++)
        {
            m_adjacency_matrix->at(i).at(j)
                = _origin.m_adjacency_matrix->at(i).at(j);

            m_link_cost->at(i).at(j)
                = _origin.m_link_cost->at(i).at(j);
        }
    }

}
t_graph::t_graph
    (const std::vector< std::vector<long double  > > _link_cost       ,
     const std::vector< std::vector<unsigned char> > _adjacency_matrix)
{
    set_graph_size(_link_cost.size());
    for(unsigned int i = 0; i < get_V_size(); i++)
    {
        for(unsigned int j = 0; j < get_V_size(); j++)
        {
            m_adjacency_matrix->at(i).at(j)
                = _adjacency_matrix.at(i).at(j);
            m_link_cost->at(i).at(j)
                = _link_cost.at(i).at(j);
        }
    }

}

t_graph::t_graph
    (const std::vector< cd::t_xy<long int> >         _node_location   ,
     const std::vector< std::vector<unsigned char> > _adjacency_matrix)
{
    set_graph_size(_node_location.size());
    for(unsigned int i = 0; i < _node_location.size(); ++i)
    {
        *m_node_location->at(i) = _node_location.at(i);
    }

    for(unsigned int i = 0; i < _adjacency_matrix.size(); ++i)
    {
        for(unsigned int j = 0; j < _adjacency_matrix.at(i).size(); ++j)
        {
            m_adjacency_matrix->at(i).at(j) = _adjacency_matrix.at(i).at(j);
            
            m_link_cost->at(i).at(j)
                = (cd::t_xy<long int>::length(
                       *m_node_location->at(i),
                       *m_node_location->at(j)));
        }
    }
}


t_graph::~t_graph()
{
}

/* method */
unsigned int t_graph::get_V_size() const
{
    return m_adjacency_matrix->size();
}

long double t_graph::get_link_cost(unsigned int _src_node_num, 
                                   unsigned int _dst_node_num) const
{
    try
    {
        if(m_adjacency_matrix->at(_src_node_num).at(_dst_node_num) == false)
            return static_cast<long double>(INFINITY);

        return m_link_cost->at(_src_node_num).at(_dst_node_num);
    }
    catch(std::out_of_range e)
    {
        return static_cast<long double>(INFINITY);
    }
}

void t_graph::set_link_cost(long     double  _link_cost   ,
                            unsigned int     _src_node_num,
                            unsigned int     _dst_node_num)
                                throw(std::out_of_range)
{
    if(_link_cost <  0                     ||
       _link_cost == (long double) INFINITY)
    {
        m_adjacency_matrix->at(_src_node_num).at(_dst_node_num)
            = false;
        m_link_cost->at(_src_node_num).at(_dst_node_num)
            = (long double) INFINITY;
        return;
    }

}

bool t_graph::to_csv(std::string _file_path)
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("graph to csv");
#endif //_DEBUG

    std::ofstream csv = std::ofstream(_file_path, std::ios::trunc);
    if(csv.fail())
        return false;

    //write index
    csv << "," << "dst" << ",";
    for(unsigned int i = 0; i < get_V_size(); ++i)
    {
        csv << std::to_string(i) << ",";
    }
    csv << std::endl;
    csv << "src" << std::endl;

    for(unsigned int i = 0; i < get_V_size(); ++i)
    {
        csv << std::to_string(i) << "," << ",";
        for(unsigned int j = 0; j < get_V_size(); ++j)
        {
            csv << ((m_adjacency_matrix->at(i).at(j))?
                        std::to_string(get_link_cost(i, j)) : 
                        "-"                                 ) << ",";
        }
        csv << std::endl;
    }
    csv.close();
    return true;
}

void t_graph::set_graph_size(unsigned int _graph_size)
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("graph size set");
#endif //_DEBUG

    m_node_location    = new std::vector< cd::t_xy<long int>* >();
    for(unsigned int i = 0; i < _graph_size; ++i)
    {
        m_node_location->push_back(new cd::t_xy<long int>(0, 0));
    }

    m_adjacency_matrix = new std::vector< std::vector<unsigned char> >();
    for(unsigned int i = 0; i < _graph_size; ++i)
    {
        m_adjacency_matrix->push_back(std::vector<unsigned char>());
        for(unsigned int j = 0; j < _graph_size; ++j)
            m_adjacency_matrix->at(i).push_back(false);
    }

    m_link_cost = new std::vector< std::vector<long double> >();
    for(unsigned int i = 0; i < _graph_size; ++i)
    {
        m_link_cost->push_back(std::vector<long double>());
        for(unsigned int j = 0; j < _graph_size; ++j)
            m_link_cost->at(i).push_back((long double)INFINITY);
    }
}



inline void t_graph::set_node_location(const unsigned int  _node_number  ,
                                       const t_xy<long int> _node_location)
                                           throw(std::out_of_range)
{
    if(_node_number >= m_node_location->size())
        throw;
    if(&_node_location == nullptr)
        return;

    m_node_location->at(_node_number) = &cd::t_xy<long int>(_node_location);

}
inline void t_graph::set_node_location(const std::vector<t_xy<long int> >
                                                 _node_location_array    ,
                                       const std::vector<unsigned char  >
                                                  _do_write               )
                                          throw(std::out_of_range)
{
    for(unsigned int i = 0; i < _node_location_array.size(); i++)
    {
        if(_do_write.at(i))
            m_node_location->at(i) = &cd::t_xy<long int>
                                         (_node_location_array.at(i));
    }
    return;
}

}