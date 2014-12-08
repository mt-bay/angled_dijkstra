#include "angled_dijkstra.hpp"

#include "../coordinate/coordinate.hpp"
#include "../coordinate/p_graph.hpp"
#include "../log/log.hpp"

namespace di
{


t_angled_dijkstra::t_angled_dijkstra
    ()
{
    init(cd::t_p_graph(), 0, 0.0, 0.0, 0.0);
}


t_angled_dijkstra::t_angled_dijkstra
    (const t_angled_dijkstra& _origin)
{
    deep_copy(_origin);
}


t_angled_dijkstra::t_angled_dijkstra
    (const cd::t_p_graph _graph          ,
     const unsigned int  _src_node_number,
     const long double   _angle_weight   ,
     const double        _accident_left  ,
     const double        _accident_right ,
     const bool          _use_dst        ,
     const unsigned int  _dst_node_number)
            throw(::std::out_of_range)
{
    init(        _graph, _src_node_number, _angle_weight,
         _accident_left,  _accident_right);

    run_dijkstra(_use_dst, _dst_node_number);
}


t_angled_dijkstra::~t_angled_dijkstra
    ()
{
    m_p_graph = cd::t_p_graph();
    
}


/* operator overload */
t_angled_dijkstra&
t_angled_dijkstra::operator= (const t_angled_dijkstra& _rhs)
{
    this->deep_copy(_rhs);
    return *this;
}


void
t_angled_dijkstra::run_dijkstra
    (const bool           _use_dst        ,
     const unsigned int   _dst_node_number)
        throw(std::out_of_range)
{
    //preprcessing
    if(m_src_node_number <                   0 ||
       m_src_node_number >= m_p_graph.get_V_size())
       throw;
    if(_use_dst                                  &&
       (_dst_node_number <                   0 ||
        _dst_node_number >= m_p_graph.get_V_size()))
       throw;

#ifdef  _DEBUG
    io::t_log::get_instance().write_line("angled dijkstra start");
#endif //_DEBUG

    //body of process
    unsigned int last_confirmed = m_src_node_number;
    while(!satisfy_end_condition(_use_dst, _dst_node_number))
    {
        for(unsigned int i = 0; i < get_V_size(); ++i)
        {
            if(i != last_confirmed                  && 
               !m_is_confirmed.at(i))
            {
                if(m_route_cost.at(last_confirmed)          +
                   m_p_graph.get_link_cost(last_confirmed, i) +
                   get_angle_cost(m_angle_weight ,
                                         last_confirmed,
                                         i             )
                   < m_route_cost.at(i))
                {
                    m_route_cost.at(i)
                        = m_route_cost.at(last_confirmed)            +
                          m_p_graph.get_link_cost(last_confirmed, i) +
                              get_angle_cost(m_angle_weight,
                                             last_confirmed,
                                             i             );

                    m_path.at(i).clear();
                    for(unsigned int j = 0;
                        j < m_path.at(last_confirmed).size();
                        ++j)
                    {
                        m_path.at(i).
                            push_back(m_path.at(last_confirmed).at(j));
                    }
                    m_path.at(i).push_back(i);
                }
            }
        }
        last_confirmed = get_confirm_node_number();
        m_is_confirmed.at(last_confirmed) = true;
    }

#ifdef _DEBUG
    io::t_log::get_instance().write_line("angled dijkstra end");
#endif //_DEBUG
    return;
}

/** 左折で事故を起こす確率：右折で事故を起こす確
 *                     4.6：8.0
 *  左折の際にかけるコストの倍率
 *  →  4.6 / 8.0
 *    = 0.575 */
inline double
t_angled_dijkstra::get_angle_cost
    (const double       _angle_weight   ,
     const unsigned int _src_node_number,
     const unsigned int _dst_node_number)
{
    double angle = path_to_angle(_src_node_number, _dst_node_number);

    return (abs(_angle_weight) < 1.0e-14)?
                0.0 :
                abs(_angle_weight
                  * sin(angle)
                  * get_angle_rate(m_accident_right, m_accident_left, angle));
}



inline double
t_angled_dijkstra::get_angle_rate
    (const double _accident_left ,
     const double _accident_right,
     const double _angle         )
{
    double calibrated_angle = std::fmod(_angle, 2 * M_PI);

    return (0 < calibrated_angle && calibrated_angle < M_PI)?
            _accident_left : _accident_right;
}

double t_dijkstra::path_to_angle
                    (unsigned int _src_node_number,
                     unsigned int _dst_node_number)
                        throw(std::out_of_range)
{
    if(_src_node_number >= m_p_graph.get_V_size() || _src_node_number < 0)
        throw;
    if(_dst_node_number >= m_p_graph.get_V_size() || _dst_node_number < 0)
        throw;

    if(m_path.at(_src_node_number).size() < 2)
    {
        return 0.0;
    }
    else
    {
        cd::t_xy<int> p0 
                    = *m_p_graph
                    . m_node_location
                    .  at(m_path.at(_src_node_number)
                    .  at(m_path.at(_src_node_number).size() - 2));

        cd::t_xy<int> p1
                    = *m_p_graph
                    .  m_node_location
                    .  at(m_path.at(_src_node_number)
                    .  at(m_path.at(_src_node_number).size() - 1));

        cd::t_xy<int> p2
                    = *m_p_graph
                    . m_node_location.at(_dst_node_number);

        return cd::t_xy<int>::get_angle(p0, p1, p2);
    }
}


void
t_angled_dijkstra::init
    (const cd::t_p_graph& _graph          ,
     const unsigned int   _src_node_number,
     const long double    _angle_weight   ,
     const double         _accident_left  ,
     const double         _accident_right )
        throw(std::out_of_range)
{
    t_dijkstra::init(_graph, _src_node_number);

    m_angle_weight   = _angle_weight;
    m_accident_left  = _accident_left;
    m_accident_right = _accident_right;
}


inline void
t_angled_dijkstra::deep_copy
    (const t_angled_dijkstra& _origin)
{
    t_dijkstra::deep_copy(_origin);

    m_angle_weight   = _origin.m_angle_weight;
    m_accident_left  = _origin.m_accident_left;
    m_accident_right = _origin.m_accident_right;

    io::t_log::get_instance().write_line(std::to_string(get_V_size()));
}


}