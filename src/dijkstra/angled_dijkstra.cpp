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


std::string
t_angled_dijkstra::get_route_cost_information
    (unsigned int _index)
{
    std::string result;

    result += std::string("index : ") + std::to_string(_index);
    result += std::string(", ") + std::string("sum. of route cost : ") +
                std::to_string(m_route_cost.at(_index));

    result += std::string("(route cost : ") +
              std::to_string(m_route_cost.at(_index) -
                             m_sum_angle_cost.at(_index));

    result += std::string(", sum. of angle cost : ")      + 
              std::to_string(m_sum_angle_cost.at(_index)) +
              std::string(")");

    return result;
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
                   get_angle_cost(m_angle_weight  ,
                                  last_confirmed  ,
                                  i               ,
                                  m_accident_left ,
                                  m_accident_right)
                   < m_route_cost.at(i))
                {
                    m_route_cost.at(i)
                        = m_route_cost.at(last_confirmed)            +
                          m_p_graph.get_link_cost(last_confirmed, i) +
                              get_angle_cost(m_angle_weight  ,
                                             last_confirmed  ,
                                             i               ,
                                             m_accident_left ,
                                             m_accident_right);

                    m_sum_angle_cost.at(i) =
                        m_sum_angle_cost.at(last_confirmed) +
                        get_angle_cost(m_angle_weight  ,
                                       last_confirmed  ,
                                       i               ,
                                       m_accident_left ,
                                       m_accident_right);

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

    m_sum_angle_cost = std::vector<long double>(m_p_graph.get_V_size(),
                                                                   0.0);
}


inline void
t_angled_dijkstra::deep_copy
    (const t_angled_dijkstra& _origin)
{
    t_dijkstra::deep_copy(_origin);

    m_angle_weight   = _origin.m_angle_weight;
    m_accident_left  = _origin.m_accident_left;
    m_accident_right = _origin.m_accident_right;

    m_sum_angle_cost.clear();
    for(std::vector<long double>::const_iterator it =
            _origin.m_sum_angle_cost.begin();
        it != _origin.m_sum_angle_cost.end();
        ++it)
    {
        m_sum_angle_cost.push_back(*it);
    }

    io::t_log::get_instance().write_line(std::to_string(get_V_size()));
}


}