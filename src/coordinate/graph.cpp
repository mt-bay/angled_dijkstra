#include <fstream>
#include <list>
#include <regex>

#include "graph.hpp"
#include "coordinate.hpp"
#include "../log/log.hpp"

#include "../tools/tools.hpp"

namespace cd
{
/* constractor and destractor */
t_graph::t_graph()
{
    set_graph_size(1);
}


t_graph::t_graph(const unsigned int _size)
{
    set_graph_size(_size);
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
    (const std::vector< cd::t_xy<int> >              _node_location   ,
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
            m_adjacency_matrix->at(i).at(j)
                = (unsigned char)
                    ((_adjacency_matrix.at(i).at(j) != 0)? true  :
                                                           false );
            
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
t_graph t_graph::csv_link_cost_to_graph(std::string _file_path)
{
    t_graph result = t_graph();

    std::ifstream csv = std::ifstream(_file_path);
    if(csv.fail())
    {
        return result;
    }

    std::string line;
    std::list< std::list<std::string> > elm;
    while(std::getline(csv, line))
    {
        elm.push_back(mt::split_l(line, ","));
    }
    
    result.set_graph_size(elm.size());
    unsigned int width = 0, height = 0;
    for(std::list< std::list<std::string> >::iterator it_h = elm.begin();
        it_h != elm.end();
        ++it_h)
    {
        for(std::list<std::string>::iterator it_w = it_h->begin();
            it_w != it_h->end();
            ++it_w)
        {
            if(it_w->find("-", 0) != std::string::npos)
            {
                result.m_adjacency_matrix->at(height).at(width) = false;
                result.set_link_cost((long double)INFINITY, height, width);
            }
            else
            {
                result.m_adjacency_matrix->at(height).at(width) = true;
                result.set_link_cost(std::stold(*it_w), height, width);
            }

            ++width;
        }
        width = 0;
        ++height;
    }
    
    csv.close();

    return result;
}


t_graph t_graph::csv_location_and_csv_adj_to_graph
                     (std::string _file_path_location,
                      std::string _file_path_adj     )
{
    t_graph result = t_graph();

    mt::mkdir(_file_path_location);
    std::ifstream csv_location = std::ifstream(_file_path_location);

    mt::mkdir(_file_path_adj);
    std::ifstream csv_adj      = std::ifstream(_file_path_adj);

    if(csv_location.fail() || csv_adj.fail())
    {
        io::t_log::get_instance().write_line("csv read failed");
        throw std::exception("csv read failed");
    }

    std::string line;
    std::vector<std::string> elm;

    //get location data
    std::vector< cd::t_xy<int> > location
        = std::vector< cd::t_xy<int> >();
    while(std::getline(csv_location, line))
    {
        elm = mt::split_v(line, ",");
        location.push_back(t_xy<int>(std::stoi(elm[0]),
                                     std::stoi(elm[1])));
    }
    csv_location.close();

    //get adj. matrix
    std::vector< std::vector<unsigned char> > adj
        = std::vector< std::vector<unsigned char> >(location.size(),
                                                    std::vector<unsigned char>
                                                        (location.size(),
                                                         false          ));
    for(unsigned int i = 0;std::getline(csv_adj, line); ++i)
    {
        elm = mt::split_v(line, ",");

        for(unsigned int j = 0; j < elm.size(); ++j)
        {
            adj.at(i).at(j) = (unsigned char)std::stoi(elm.at(j));
        }
    }
    csv_adj.close();

    result.set_graph_size(location.size());
    for(unsigned int i = 0; i < location.size(); ++i)
    {
        *result.m_node_location->at(i) = location.at(i);
    }
    for(unsigned int i = 0; i < adj.size(); ++i)
    {
        for(unsigned int j = 0; j < adj.at(i).size(); ++j)
        {
            result.m_adjacency_matrix->at(i).at(j)
                = (unsigned char)((adj.at(i).at(j) != 0)? true : false);
            result.m_link_cost->at(i).at(j)
                = cd::t_xy<long int>::length(location.at(i), location.at(j));
        }
    }

    return result;

}


unsigned int t_graph::get_V_size() const
{
    return m_adjacency_matrix->size();
}


long double t_graph::get_link_cost(const unsigned int _src_node_num, 
                                   const unsigned int _dst_node_num) const
{
    try
    {
        if(m_adjacency_matrix->at(_src_node_num).at(_dst_node_num))
        {
            return m_link_cost->at(_src_node_num).at(_dst_node_num);
        }
    }
    catch(std::out_of_range ignored)
    {
    }
    return static_cast<long double>(INFINITY);
}


unsigned char t_graph::get_adjacency(const unsigned int _src_node_num,
                                     const unsigned int _dst_node_num) const
{
    try
    {
        if(m_adjacency_matrix->at(_src_node_num).at(_dst_node_num))
        {
            return static_cast<unsigned char>(1);
        }
    }
    catch(std::out_of_range ignored)
    {
    }
    return static_cast<unsigned char>(0);
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

    m_adjacency_matrix->at(_src_node_num).at(_dst_node_num)
            = true;
    m_link_cost->at(_src_node_num).at(_dst_node_num)
            = _link_cost;
}


bool t_graph::to_csv(std::string _file_path, bool _write_index)
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("graph to csv");
#endif //_DEBUG

    mt::mkdir(_file_path);
    std::ofstream csv = std::ofstream(_file_path, std::ios::trunc);
    if(csv.fail())
        return false;

    //write index
    if(_write_index)
    {
        csv << "," << "dst" << ",";
        for(unsigned int i = 0; i < get_V_size(); ++i)
        {
            csv << std::to_string(i) << ",";
        }
        csv << std::endl;
        csv << "src" << std::endl;
    }

    for(unsigned int i = 0; i < get_V_size(); ++i)
    {
        if(_write_index)
        {
            csv << std::to_string(i) << "," << ",";
        }

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

bool t_graph::to_adj_and_loc_csv(const std::string _location_file_path,
                                 const std::string _adjacency_file_path)
    const
{
    try
    {
        mt::mkdir(_location_file_path);
        std::ofstream location_csv = std::ofstream(_location_file_path);

        for(unsigned int i = 0; i < m_node_location->size(); ++i)
        {
            location_csv << m_node_location->at(i)->x << ","
                         << m_node_location->at(i)->y << std::endl;
        }
        location_csv.close();

        mt::mkdir(_adjacency_file_path);
        std::ofstream adjacency_csv = std::ofstream(_adjacency_file_path);
        for(unsigned int i = 0; i < m_adjacency_matrix->size(); ++i)
        {
            for(unsigned int j = 0; j < m_adjacency_matrix->at(i).size(); ++j)
            {
                adjacency_csv << ((m_adjacency_matrix->at(i).at(j))?
                                    "1" : "0");
                
                if(j < m_adjacency_matrix->at(i).size() - 1)
                {
                    adjacency_csv << ",";
                }
            }
            adjacency_csv << std::endl;
        }
        adjacency_csv.close();
        
        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}


void t_graph::add_graph_size(unsigned int _add_graph_size)
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("graph size add");
#endif //_DEBUG
    for(unsigned int i = 0; i < _add_graph_size; ++i)
    {
        m_node_location->push_back(new cd::t_xy<int>(0, 0));
        m_adjacency_matrix->push_back
            (std::vector<unsigned char>(m_adjacency_matrix->size(), false));

        m_link_cost->push_back
            (std::vector<long double>(0));

        for(unsigned int j = 0; j < m_adjacency_matrix->size(); ++j)
        {
            m_adjacency_matrix->at(i).push_back(false);
            m_link_cost->at(i).push_back((long double)INFINITY);
        }
    }

}


void t_graph::set_graph_size(unsigned int _graph_size)
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("graph size set");
#endif //_DEBUG

    m_node_location    = new std::vector< cd::t_xy<int>* >(0);
    for(unsigned int i = 0; i < _graph_size; ++i)
    {
        m_node_location->push_back(new cd::t_xy<int>(0, 0));
    }

    m_adjacency_matrix = new std::vector< std::vector<unsigned char> >
                                 (0, std::vector<unsigned char>(0));
    for(unsigned int i = 0; i < _graph_size; ++i)
    {
        m_adjacency_matrix->push_back(std::vector<unsigned char>(0));
        for(unsigned int j = 0; j < _graph_size; ++j)
            m_adjacency_matrix->at(i).push_back(false);
    }

    m_link_cost = new std::vector< std::vector<long double> >
                          (0, std::vector<long double>(0));
    for(unsigned int i = 0; i < _graph_size; ++i)
    {
        m_link_cost->push_back(std::vector<long double>(0));
        for(unsigned int j = 0; j < _graph_size; ++j)
            m_link_cost->at(i).push_back((long double)INFINITY);
    }
}


inline void t_graph::set_node_location(const unsigned int _node_number  ,
                                       const t_xy<int>    _node_location)
                                           throw(std::out_of_range)
{
    if(_node_number >= m_node_location->size())
        throw;
    if(&_node_location == nullptr)
        return;

    m_node_location->at(_node_number) = new cd::t_xy<int>(_node_location);

}


inline void t_graph::set_node_location(const std::vector<t_xy<int> >
                                                 _node_location_array  ,
                                       const std::vector<unsigned char>
                                                  _do_write            )
                                          throw(std::out_of_range)
{
    for(unsigned int i = 0; i < _node_location_array.size(); i++)
    {
        if(_do_write.at(i))
            m_node_location->at(i) = new cd::t_xy<int>
                                         (_node_location_array.at(i));
    }
    return;
}

}