#include <fstream>
#include <list>
#include <iomanip>

#include <algorithm>

#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"
#include "../coordinate/p_graph.hpp"

#include "../dijkstra/dijkstra.hpp"

#include "../log/log.hpp"

#include "../tools/define.hpp"
#include "../tools/tools.hpp"

namespace jmc
{

t_JMC::t_JMC()
{
    m_primary_mesh = std::map<int, t_primary_mesh >();
}


t_JMC::t_JMC(const di::t_dijkstra& _dijkstra) : t_JMC::t_JMC()
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("dijkstra result to JMC file(s)");
#endif // _DEBUG

    m_primary_mesh = std::map<int, t_primary_mesh >();

    std::vector<unsigned int>::iterator it_path;
    std::list< cd::t_xy<int> > buf_path;

    for(unsigned int i = 0; i < _dijkstra.m_path->size(); ++i)
    {
        buf_path.clear();
        for(it_path =  _dijkstra.m_path->at(i).begin();
            it_path != _dijkstra.m_path->at(i).end();
            ++it_path                                  )
        {
            buf_path
                .push_back(*_dijkstra.m_p_graph.m_node_location.at(*it_path));
        }
        add_path(buf_path);
    }
}


t_JMC::t_JMC(const di::t_dijkstra& _dijkstra, std::vector<unsigned int> _part)
{
    m_primary_mesh = std::map<int, t_primary_mesh >();

    std::vector<unsigned int>::iterator it_path;
    std::list< cd::t_xy<int> > buf_path;

    for(unsigned int i = 0; i < _dijkstra.m_path->size(); ++i)
    {
        if(mt::find(_part, i))
        {
            io::t_log::get_instance().write_line("write line " + std::to_string(i));
            buf_path.clear();
         for(it_path =  _dijkstra.m_path->at(i).begin();
                it_path != _dijkstra.m_path->at(i).end();
                ++it_path                                  )
            {
             buf_path
                 .push_back(*_dijkstra.m_p_graph.m_node_location.at(*it_path));
            }
            add_path(buf_path);
        }
    }
}

t_JMC::t_JMC(const cd::t_p_graph& _p_graph, unsigned int _src)
{
    m_primary_mesh = std::map<int, t_primary_mesh >();

    std::vector<unsigned int>::const_iterator it_adj;
    std::list< cd::t_xy<int> > buf_path;

    unsigned int index = _src;

    for(unsigned int i = 0; i < _p_graph.get_V_size(); ++i)
    {
        buf_path.push_back(*_p_graph.m_node_location.at(index));
        if(_p_graph.m_adjacency.at(index).size() <= 0)
        {
            break;
        }
        index = _p_graph.m_adjacency.at(index).at(0);
    }
    add_path(buf_path);

}


t_JMC::~t_JMC()
{

}


bool t_JMC::output(const std::string _output_directory) const
{
    try
    {
        std::string file_name;

        std::ofstream out_file;

        mt::mkdir(_output_directory);

        for(std::map<int, t_primary_mesh >::const_iterator it
                = m_primary_mesh.begin();
            it != m_primary_mesh.end();
            ++it)
        {
            file_name = _output_directory
                        + "KS" + std::to_string(it->first) + ".DAT";
            out_file = std::ofstream(file_name);
            out_file << it->second.to_string();
            out_file.close();
        }

        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}


void t_JMC::add_path(const std::list<cd::t_xy<int> >& _path)
{
    if(_path.size() < 2)
    {
        return;
    }

    std::map<int, std::list< cd::t_xy<int> > > buf_path_map;
    std::vector< cd::t_xy<int> > buf_path;

    std::list< cd::t_xy<int> >::const_iterator it_before =  _path.begin();
    std::vector<int> buf_primary_mesh_before;

    cd::t_xy<int> buf_xy_int = cd::t_xy<int>();

    std::vector<int> buf_primary_mesh;
    for(std::list< cd::t_xy<int> >::const_iterator it = ++_path.begin();
        it != _path.end();
        true)
    {
        buf_primary_mesh_before = location_to_primary_mesh(*it_before);
        buf_primary_mesh = location_to_primary_mesh(*it);

        buf_path.push_back(*it_before);

        for(int i = 0; i < buf_primary_mesh_before.size(); ++i)
        {
            for(int j = 0; j < buf_primary_mesh.size(); ++j)
            {
                if(buf_primary_mesh_before.at(i) != buf_primary_mesh.at(j))
                {
                    if(   (buf_primary_mesh_before.at(i) / 100)
                       != (buf_primary_mesh.at(j)        / 100))
                    {
                        buf_xy_int.y = (buf_primary_mesh.at(j) / 100)
                                     * SECONDARY_MESH_MAX * MESH_LOCATION_MAX_Y;

                        buf_xy_int.y = (buf_primary_mesh.at(j) / 100)
                                     * SECONDARY_MESH_MAX * MESH_LOCATION_MAX_Y;
                    }
                }
            }
        }

        ++it_before;
        ++it;
    }

    buf_path.push_back(*(--_path.end()));

    for(std::list< cd::t_xy<int> >::const_iterator it = ++_path.begin();
        it != _path.end();
        true)
    {
        buf_primary_mesh = location_to_primary_mesh(*it);
        for(unsigned int i = 0; i < buf_primary_mesh.size(); ++i)
        {
            if(buf_path_map.count(buf_primary_mesh.at(i)) == 0)
            {
                buf_path_map[buf_primary_mesh.at(i)]
                    = std::list< cd::t_xy<int> >();
            }
            buf_path_map[buf_primary_mesh.at(i)].push_back(cd::t_xy<int>(*it));
        }

        ++it_before;
        ++it;
    }

    for(std::map<int, std::list< cd::t_xy<int> > >::iterator it
            = buf_path_map.begin();
        it != buf_path_map.end();
        ++it)
    {
        if(it->second.size() >= 2)
        {
            if(m_primary_mesh.count(it->first) == 0)
            {
                m_primary_mesh[it->first] = t_primary_mesh(it->first);
            }
            m_primary_mesh[it->first].add_path(it->second);
        }
    }
}


}