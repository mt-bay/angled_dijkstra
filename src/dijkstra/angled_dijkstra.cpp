#include "angled_dijkstra.hpp"

#include "../coordinate/coordinate.hpp"
#include "../coordinate/graph.hpp"
#include "../log/log.hpp"

namespace di
{
t_angled_dijkstra::t_angled_dijkstra()
{
    init(cd::t_graph(), 0);
}


t_angled_dijkstra::t_angled_dijkstra(const t_angled_dijkstra& _origin)
{
    deep_copy(_origin);
}


t_angled_dijkstra::t_angled_dijkstra(const cd::t_graph  _graph          ,
                                     const unsigned int _src_node_number)
                                        throw(std::out_of_range)
{
    init(_graph, _src_node_number);
}


t_angled_dijkstra t_angled_dijkstra::gen_dijkstra
                (const cd::t_graph  _graph          ,
                 const long double  _angle_weight   ,
                 const unsigned int _src_node_number,
                 const bool         _use_dst        ,
                 const unsigned int _dst_node_number)
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

    t_angled_dijkstra result = t_angled_dijkstra(_graph, _src_node_number);
    
#ifdef  _DEBUG
    io::t_log::get_instance().write_line("angled dijkstra start");
#endif //_DEBUG

    //body of process
    unsigned int last_confirmed = _src_node_number;
    while(!result.satisfy_end_condition(_use_dst, _dst_node_number))
    {
        for(unsigned int i = 0; i < _graph.get_V_size(); ++i)
        {
            if(i != last_confirmed                  && 
               result.m_is_confirmed->at(i) == false)
            {
                if(result.m_route_cost->at(last_confirmed)          +
                   result.m_graph->get_link_cost(last_confirmed, i) +
                   result.get_angle_cost(_angle_weight ,
                                         last_confirmed,
                                         i             )
                   < result.m_route_cost->at(i))
                {
                    result.m_route_cost->at(i)
                        = result.m_route_cost->at(last_confirmed)          +
                          result.m_graph->get_link_cost(last_confirmed, i) +
                              result.get_angle_cost(_angle_weight ,
                                                    last_confirmed,
                                                    i             );

                    result.m_path->at(i) 
                        = std::vector<unsigned int>();
                    for(unsigned int j = 0;
                        j < result.m_path->at(last_confirmed).size();
                        ++j)
                    {
                        result.m_path->at(i).
                            push_back(result.m_path->at(last_confirmed).at(j));
                    }
                    result.m_path->at(i).push_back(i);
                }
            }
        }
        last_confirmed = result.get_confirm_node_number();
        result.m_is_confirmed->at(last_confirmed) = true;
    }

#ifdef _DEBUG
    io::t_log::get_instance().write_line("angled dijkstra end");
#endif //_DEBUG
    return result;
}


inline double t_angled_dijkstra::get_angle_cost
                    (const double       _angle_weight   ,
                     const unsigned int _src_node_number,
                     const unsigned int _dst_node_number)
{
    return (abs(_angle_weight) < 1.0e-14)?
                0.0 :
                abs(_angle_weight * sin(path_to_angle(_src_node_number,
                                                      _dst_node_number)));
}


double t_angled_dijkstra::path_to_angle
                    (unsigned int _src_node_number,
                     unsigned int _dst_node_number)
                        throw(std::out_of_range)
{
    if(_src_node_number >= m_graph->get_V_size() || _src_node_number < 0)
        throw;
    if(_dst_node_number >= m_graph->get_V_size() || _dst_node_number < 0)
        throw;

    if(m_path->at(_src_node_number).size() < 2)
    {
        return 0.0;
    }
    else
    {
        cd::t_xy<int> p0 
                    = *m_graph
                    -> m_node_location
                    -> at(m_path->at(_src_node_number)
                    .  at(m_path->at(_src_node_number).size() - 2));

        cd::t_xy<int> p1
                    = *m_graph
                    -> m_node_location
                    -> at(m_path->at(_src_node_number)
                    .  at(m_path->at(_src_node_number).size() - 1));

        cd::t_xy<int> p2
                    = *m_graph
                    -> m_node_location->at(_dst_node_number);

        return cd::t_xy<int>::get_angle(p0, p1, p2);
    }
}

}