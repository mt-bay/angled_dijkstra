#include "dijkstra.hpp"
#include "../tools/graph.hpp"
#include "../tools/coordinate.hpp"


namespace di
{
/* constractor and destractor */
t_dijkstra::t_dijkstra()
{
    init(cd::t_graph(), 0);
}


t_dijkstra::t_dijkstra(const t_dijkstra& _origin)
{
    deep_copy(_origin);
}


t_dijkstra::t_dijkstra(const cd::t_graph  _graph          ,
                       const unsigned int _src_node_number)
                          throw(std::out_of_range)
{
    init(_graph, _src_node_number);
}


/* method */
unsigned int t_dijkstra::get_V_size() const
{
    return m_route_cost->size();
}

t_dijkstra t_dijkstra::gen_dijkstra(const cd::t_graph  _graph          , 
                                    const unsigned int _src_node_number,
                                    const unsigned int _dst_node_number,
                                    const bool         _use_dst        )
                                        throw(std::out_of_range)
{
    return gen_dijkstra_angled(_graph, 0, 0, 0.0, _use_dst);
}


t_dijkstra t_dijkstra::gen_dijkstra_angled(const cd::t_graph  _graph          ,
                                           const unsigned int _src_node_number,
                                           const unsigned int _dst_node_number,
                                           const long double  _angle_weight   ,
                                           const bool         _use_dst        )
                                               throw(std::out_of_range)
{
    //preprcessing
    if(_src_node_number <                   0 ||
       _src_node_number >= _graph.get_V_size())
       throw;
    if(_use_dst                                  &&
       (_dst_node_number <                   0 ||
        _dst_node_number >= _graph.get_V_size()))
       throw;

    t_dijkstra result = t_dijkstra(_graph, _src_node_number);

    //body of process
    unsigned int last_confirmed = _src_node_number;
    while(result.satisfy_end_condition(_use_dst, _dst_node_number))
    {
        for(unsigned int i = 0; i < _graph.get_V_size(); ++i)
        {
            if(i != last_confirmed                  && 
               result.m_is_confirmed->at(i) == false)
            {
                if(result.m_route_cost->at(last_confirmed) +
                   result.get_angle_cost(_angle_weight ,
                                         last_confirmed,
                                         i             )
                   < result.m_route_cost->at(i))
                {
                    result.m_route_cost->at(i)
                        = result.m_route_cost->at(last_confirmed) +
                              result.get_angle_cost(_angle_weight ,
                                                    last_confirmed,
                                                    i             );
                    result.m_path->at(i) 
                        = std::vector<unsigned int>
                              (result.m_path->at(_src_node_number));
                    result.m_path->at(i).push_back(i);

                }
            }
        }
        last_confirmed = result.get_confirm_node_number();
        result.m_is_confirmed->at(last_confirmed) = true;
    }

    return result;
}

inline double t_dijkstra::get_angle_cost(const double       _angle_weight   ,
                                         const unsigned int _src_node_number,
                                         const unsigned int _dst_node_number)
{
    return abs(_angle_weight * sin(path_to_angle(_src_node_number,
                                                 _dst_node_number)));
}

double t_dijkstra::path_to_angle(unsigned int _src_node_number,
                                 unsigned int _dst_node_number)
                                     throw(std::out_of_range)
{
    if(_src_node_number >= m_path->size()        || _src_node_number < 0)
        throw;
    if(_dst_node_number >= m_graph->get_V_size() || _dst_node_number < 0)
        throw;

    if(m_path->at(_src_node_number).size() < 2)
    {
        return 0.0;
    }
    else
    {
        cd::t_xy<long int> p0 
                           = *m_graph->
                             m_node_location->
                             at(m_path->at(_src_node_number).
                                 at(m_path->at(_src_node_number).size() - 2));

        cd::t_xy<long int> p1
                           = *m_graph->
                             m_node_location->
                             at(m_path->at(_src_node_number).
                                 at(m_path->at(_src_node_number).size() - 1));

        cd::t_xy<long int> p2
                           = *m_graph->
                             m_node_location->at(_dst_node_number);

        return cd::t_xy<long int>::get_angle(p0, p1, p2);
    }
}


bool t_dijkstra::satisfy_end_condition(const bool         _use_dst        ,
                                       const unsigned int _dst_node_number)
{
    if(_use_dst)
    {
        return m_is_confirmed->at(_dst_node_number);
    }
    else
    {
        for(unsigned int i = 0; i < m_is_confirmed->size(); ++i)
        {
            if(m_is_confirmed->at(i) == false)
                return false;
        }
        return true;
    }
}


unsigned int t_dijkstra::get_confirm_node_number()
{
    unsigned int candidature     = 0;
    long double  candidature_val = (long double)INFINITY;
    for(unsigned int i = 0; i < m_route_cost->size(); ++i)
    {
        if(!m_is_confirmed->at(i) &&
           m_route_cost->at(i) < candidature_val)
        {
            candidature = i;
            candidature_val = m_route_cost->at(i);
        }
    }

    return candidature;
}

inline void t_dijkstra::set_graph_size(const unsigned int _graph_size)
{
    m_route_cost = & std::vector<long double>(_graph_size, 0.0);
    m_path       = &std::vector< std::vector<unsigned int> >
                       (_graph_size, std::vector<unsigned int>
                                         (0, 0));
}


inline void t_dijkstra::init(const cd::t_graph  _graph          ,
                             const unsigned int _src_node_number)
                                throw(std::out_of_range)
{
    if(_src_node_number >= _graph.get_V_size())
        throw;

    m_graph           = &cd::t_graph(_graph);

    m_src_node_number = _src_node_number;
    m_route_cost      = &std::vector<long double>  (_graph.get_V_size(),
                                                    (long double)INFINITY);

    m_is_confirmed    = &std::vector<unsigned char>(_graph.get_V_size(),
                                                    false);

        m_path            = &std::vector< std::vector<unsigned int> >
                          (_graph.get_V_size(), std::vector<unsigned int>());

    m_route_cost->at(_src_node_number) = 0.0;
    m_path->at(_src_node_number).push_back(_src_node_number);
    m_is_confirmed->at(_src_node_number) = true;

}


inline void t_dijkstra::deep_copy(const t_dijkstra& _origin)
{
    m_src_node_number =  _origin.m_src_node_number;

    m_route_cost      = &std::vector<long double>
                            (_origin.get_V_size());
    for(unsigned int i = 0; i < m_route_cost->size(); ++i)
        m_route_cost->at(i) = _origin.m_route_cost->at(i);
    
    m_is_confirmed    = &std::vector<unsigned char>
                            (_origin.get_V_size());
    for(unsigned int i = 0;i < _origin.get_V_size(); ++i)
        m_is_confirmed->at(i) = _origin.m_is_confirmed->at(i);

    m_path            = &std::vector< std::vector<unsigned int> >
                            (_origin.get_V_size());
    for(unsigned int i = 0; i < _origin.get_V_size(); ++i)
    {
        m_path->at(i) = std::vector<unsigned int>
                            (_origin.m_path->at(i).size());
        for(unsigned int j = 0; j < _origin.m_path->at(i).size(); ++j)
        {
            m_path->at(i).at(j) = _origin.m_path->at(i).at(j);
        }
    }
}

}