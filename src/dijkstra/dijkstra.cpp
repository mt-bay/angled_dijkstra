#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

#include "dijkstra.hpp"
#include "../coordinate/p_graph.hpp"
#include "../coordinate/coordinate.hpp"

#include "../log/log.hpp"

#include "../tools/tools.hpp"
#include "../tools/define.hpp"

namespace di
{
/* constractor and destractor */
t_dijkstra::t_dijkstra()
{
    init(cd::t_p_graph(), 0);
}


t_dijkstra::t_dijkstra(const t_dijkstra& _origin)
{
    deep_copy(_origin);
}


t_dijkstra::t_dijkstra
    (const cd::t_p_graph _graph          ,
     const unsigned int  _src_node_number,
     const bool          _use_dst        ,
     const unsigned int  _dst_node_number)
        throw(std::out_of_range)
{
    init(_graph, _src_node_number);

    run_dijkstra(_use_dst, _dst_node_number);
}


t_dijkstra::~t_dijkstra()
{

}


/* operator overload */
t_dijkstra& t_dijkstra::operator= (const t_dijkstra& _rhs)
{
    this->deep_copy(_rhs);
    return *this;
}


/* method */
void
t_dijkstra::run_dijkstra
    (const bool          _use_dst        ,
     const unsigned int  _dst_node_number)
        throw(std::out_of_range)
{
    //preprcessing
    if(m_src_node_number <                   0 ||
       m_src_node_number > m_p_graph.get_V_size() - 1)
       throw;
    if(_use_dst                                  &&
       (_dst_node_number <                   0 ||
        _dst_node_number >= m_p_graph.get_V_size()))
       throw;

#ifdef  _DEBUG
    io::t_log::get_instance().write_line("dijkstra start");
#endif //_DEBUG

    //body of process
    unsigned int last_confirmed = m_src_node_number;

    while(!satisfy_end_condition(_use_dst, _dst_node_number))
    {
        for(unsigned int i = 0; i < m_p_graph.get_V_size(); ++i)
        {
            if(i != last_confirmed                  && 
               m_is_confirmed.at(i) == false)
            {
                if(m_route_cost.at(last_confirmed)          +
                   m_p_graph.get_link_cost(last_confirmed, i)
                   < m_route_cost.at(i))
                {
                    m_route_cost.at(i)
                        = m_route_cost.at(last_confirmed)          +
                          m_p_graph.get_link_cost(last_confirmed, i);

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
    io::t_log::get_instance().write_line("dijkstra end");
#endif //_DEBUG
    return;
}




unsigned int t_dijkstra::get_V_size() const
{
    return m_route_cost.size();
}


bool t_dijkstra::to_csv(const std::string _file_path) const
{

#ifdef _DEBUG
    io::t_log::get_instance().write_line("dijkstra result to csv");
#endif //_DEBUG

    mt::mkdir(_file_path);
    std::ofstream csv = std::ofstream(_file_path, std::ios::trunc);
    if(csv.fail())
        return false;

    const std::string csv_separator = ",";
    size_t   node_num_length
                = std::to_string(m_p_graph.get_V_size() - 1).length();

    std::string   path_separator = ";";

    auto path_to_string
        = [](std::vector<unsigned int> _path,
             std::string          _separator,
             unsigned int           _elm_len)
             -> std::string const
            {
                std::stringstream ss;
                std::string return_val;
                for(unsigned int i = 0; i < _path.size(); ++i)
                {
                    ss << std::setw(_elm_len) << std::right << _path.at(i);
                    ss << _separator;
                }
                return ss.str();
            };
    
    csv << "index"       << csv_separator;
    csv << "path.length" << csv_separator;
    csv << "path"        << csv_separator;
    csv << "cost"        << std::endl;
    for(unsigned int i = 0; i < m_path.size(); ++i)
    {
        csv << i << csv_separator;
        csv << m_path.at(i).size() << csv_separator;
        csv << path_to_string(m_path.at(i)  ,
                              path_separator ,
                              node_num_length) << csv_separator;
        csv << m_route_cost.at(i) << std::endl;
    }

    csv.close();
    return true;
}


cd::t_p_graph t_dijkstra::to_p_graph() const
{
    cd::t_p_graph result = cd::t_p_graph();
    
    for(unsigned int i = 0; i < m_p_graph.m_node_location.size(); ++i)
    {
        result.add_node(*m_p_graph.m_node_location.at(i));
    }

    for(unsigned int i = 0; i < m_path.size(); ++i)
    {
        for(unsigned int j = 1; j < m_path.at(i).size(); ++j)
        {
            result.set_adjacency(m_path.at(i).at(j - 1),
                                 m_path.at(i).at(j    ),
                                 true);
        }
    }

    return result;
}


cd::t_p_graph t_dijkstra::to_p_graph_part_of
                            (const std::vector<unsigned int>& _dst)
                                            const
{    
    cd::t_p_graph result = cd::t_p_graph();
    std::vector<unsigned int>::const_iterator it_before;
    std::vector<unsigned int>::const_iterator it;

    for(unsigned int i = 0; i < m_p_graph.m_node_location.size(); ++i)
    {
        result.add_node(*m_p_graph.m_node_location.at(i));
    }
    for(unsigned int i = 0; i < get_V_size(); ++i)
    {
        if(mt::find(_dst, i))
        {
            it_before = m_path.at(i).begin();
           for(it =  it_before + 1;
               it != m_path.at(i).end();
               ++it)
            {
                result.set_adjacency(*it_before, *it, true);
                it_before = it;
            }
        }
    }

    return result;
}


inline void t_dijkstra::deep_copy(const t_dijkstra& _origin)
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("dijkstra deep copy");
#endif //_DEBUG

    m_p_graph = cd::t_p_graph(_origin.m_p_graph);

    m_src_node_number =  _origin.m_src_node_number;

    m_route_cost      = std::vector<long double>
                            (_origin.get_V_size());
    for(unsigned int i = 0; i < m_route_cost.size(); ++i)
        m_route_cost.at(i) = _origin.m_route_cost.at(i);
    
    m_is_confirmed    = std::vector<unsigned char>
                            (_origin.get_V_size());
    for(unsigned int i = 0;i < _origin.get_V_size(); ++i)
        m_is_confirmed.at(i) = _origin.m_is_confirmed.at(i);

    m_path            = std::vector< std::vector<unsigned int> >
                            (_origin.get_V_size());
    for(unsigned int i = 0; i < _origin.get_V_size(); ++i)
    {
        m_path.at(i) = std::vector<unsigned int>
                            (_origin.m_path.at(i).size());
        for(unsigned int j = 0; j < _origin.m_path.at(i).size(); ++j)
        {
            m_path.at(i).at(j) = _origin.m_path.at(i).at(j);
        }
    }
}


int t_dijkstra::find_secondary_mesh_is(std::ofstream* _search_file_ofs) const
{
    return 0;
}


unsigned int t_dijkstra::get_confirm_node_number() const
{
    unsigned int candidature     = -1;
    long double  candidature_val = (long double)INFINITY;
    for(unsigned int i = 0; i < m_route_cost.size(); ++i)
    {
        if(!m_is_confirmed.at(i)             &&
           (m_route_cost.at(i) < candidature_val ||
            candidature == -1))
        {
            candidature = i;
            candidature_val = m_route_cost.at(i);
        }
    }

    return candidature;
}


inline void t_dijkstra::init(const cd::t_p_graph& _graph          ,
                             const unsigned int   _src_node_number)
                                throw(std::out_of_range)
{
    m_p_graph         = cd::t_p_graph(_graph);

    m_src_node_number = _src_node_number;

    m_route_cost      = std::vector<long double>  (m_p_graph.get_V_size(),
                                                   (long double)INFINITY);

    m_is_confirmed    = std::vector<unsigned char>(m_p_graph.get_V_size(),
                                                   false              );

    m_path            = std::vector< std::vector<unsigned int> >
                          (_graph.get_V_size(), std::vector<unsigned int>());

    if(m_path.size() <= _src_node_number)
    {
        return;
    }
    m_route_cost.at(_src_node_number) = 0.0;
    m_path.at(_src_node_number).push_back(_src_node_number);
    m_is_confirmed.at(_src_node_number) = true;

}





bool t_dijkstra::satisfy_end_condition(const bool         _use_dst        ,
                                       const unsigned int _dst_node_number)
{
#ifdef _DEBUG
    io::t_log::get_instance().write("check satisfy end condition");
    io::t_log::get_instance().write_line("(dst is " + ((_use_dst)?
                                             std::to_string(_dst_node_number) :
                                             "none")
                                         + ")");
#endif //_DEBUG


    if(_use_dst)
    {
        return (m_is_confirmed.at(_dst_node_number) != (unsigned char)false);
    }
    else
    {
        for(unsigned int i = 0; i < m_is_confirmed.size(); ++i)
        {
            if(m_is_confirmed.at(i) == (unsigned char)false)
                return false;
        }
        return true;
    }
}


inline void t_dijkstra::set_graph_size(const unsigned int _graph_size)
{
    m_route_cost = std::vector<long double>(_graph_size, 0.0);
    m_path       = std::vector< std::vector<unsigned int> >
                       (_graph_size, std::vector<unsigned int>
                                         (0, 0));
}

}