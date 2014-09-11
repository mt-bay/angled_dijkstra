#include "graph.hpp"
#include "coordinate.hpp"

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
        *m_node_location->at(i) = *_origin.m_node_location->at(i);
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
        m_node_location->at(i) = nullptr;
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
    for(unsigned int i = 0; i < m_node_location->size(); i++)
        *m_node_location->at(i) = _node_location.at(i);

    for(unsigned int i = 0; i < get_V_size(); i++)
    {
        for(unsigned int j = 0; j < get_V_size(); j++)
        {
            m_adjacency_matrix->at(i).at(j)
                = _adjacency_matrix.at(i).at(j);
            m_link_cost->at(i).at(j)
                = cd::t_xy<long int>::length(*m_node_location->at(i),
                                             *m_node_location->at(j));
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

inline void t_graph::set_graph_size(unsigned int _graph_size)
{
    m_node_location    = &std::vector<cd::t_xy<long int>* >
                             (_graph_size, &cd::t_xy<long int>(0, 0));

    m_adjacency_matrix = &std::vector< std::vector<unsigned char> >
                              (_graph_size, std::vector<unsigned char>
                                                (_graph_size, false));

    m_link_cost        = &std::vector< std::vector<long double> >
                              (_graph_size, std::vector<long double>
                                                (_graph_size, 
                                                 (long double)INFINITY));
}



inline void t_graph::set_node_location(const unsigned int  _node_number  ,
                                       const t_xy<long int> _node_location)
                                           throw(std::out_of_range)
{
    if(_node_number >= m_node_location->size())
        throw;
    if(&_node_location == nullptr)
        return;

    *m_node_location->at(_node_number) = _node_location;

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
            *m_node_location->at(i) = _node_location_array.at(i);
    }
    return;
}

}