#include <fstream>
#include <list>
#include <iomanip>

#include <algorithm>

#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"
#include "../coordinate/p_graph.hpp"

#include "../log/log.hpp"

#include "../tools/define.hpp"
#include "../tools/tools.hpp"

namespace jmc
{

t_JMC::t_JMC()
{
    m_primary_mesh = std::map<int, t_primary_mesh >();
}


t_JMC::t_JMC
    (const t_JMC& _origin)
{
    deep_copy(_origin);
}


t_JMC::t_JMC(const cd::t_p_graph& _p_graph, unsigned int _src)
{
    m_primary_mesh = std::map<int, t_primary_mesh >();

    std::vector< std::list< cd::t_xy<int> > > buf_path_array =
        get_path_array(_p_graph, _src);

    for(std::vector< std::list< cd::t_xy<int> > >::iterator it =
            buf_path_array.begin();
        it != buf_path_array.end();
        ++it)
    {
        add_path(*it);
    }
}

t_JMC::t_JMC(const std::string _jmc_dir)
    : t_JMC()
{
    std::list<std::string> file_list =
        mt::get_file_path_list(_jmc_dir, "*.DAT");

    std::string dir_path = _jmc_dir + ((_jmc_dir.back() == '\\')? "" : "\\");

    std::string buf_str;
    int buf_mesh_number;

    for(std::list<std::string>::iterator it = file_list.begin();
        it != file_list.end();
        ++it)
    {
        buf_str = it->substr(2, 4);
        buf_mesh_number = std::stoi(buf_str);
        m_primary_mesh[buf_mesh_number] = 
            t_primary_mesh(dir_path + (*it), buf_mesh_number);
    }
}


t_JMC::~t_JMC()
{

}


t_JMC&
t_JMC::operator=
    (const t_JMC& _rhs)
{
    deep_copy(_rhs);
    return *this;
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
            if(out_file.fail())
            {
                io::t_log::get_instance().write_line
                    (file_name + "open failed");
                continue;
            }

            out_file << it->second.to_string() << std::flush;
            out_file.close();
        }

        return true;
    }
    catch(std::exception e)
    {
        return false;
    }
}


bool t_JMC::is_exist
    (const cd::t_xy<int>& _src,
     const cd::t_xy<int>& _dst)
const
{
    std::vector<int> src_primary = location_to_primary_mesh(_src);
    std::vector<int> dst_primary = location_to_primary_mesh(_dst);

    //checking src's target primary mesh exist
    bool exist_primary_mesh = false;
    for(std::vector<int>::iterator it = src_primary.begin();
        it != src_primary.end();
        true)
    {
        if(m_primary_mesh.find(*it) != m_primary_mesh.cend())
        {
            exist_primary_mesh = true;
            ++it;
        }
        else
        {
            it = src_primary.erase(it);
        }
    }
    if(!exist_primary_mesh)
    {
        return false;
    }

    //checking dst's target primary mesh exist
    exist_primary_mesh = false;
    for(std::vector<int>::iterator it = dst_primary.begin();
        it != dst_primary.end();
        true)
    {
        if(m_primary_mesh.find(*it) != m_primary_mesh.end())
        {
            exist_primary_mesh = true;
            ++it;
        }
        else
        {
            it = dst_primary.erase(it);
        }
    }
    if(!exist_primary_mesh)
    {
        return false;
    }

    std::vector<int> src_secondary = location_to_secondary_mesh(_src);
    std::vector<int> dst_secondary = location_to_secondary_mesh(_dst);

    int buf_primary_mesh;

    //trim src secondary mesh vector
    for(std::vector<int>::const_iterator it = src_secondary.begin();
        it != src_secondary.end();
        true)
    {
        buf_primary_mesh = secondary_mesh_to_primary_mesh(*it);

        if(std::find(src_primary.begin(),
                     src_primary.end()  ,
                     buf_primary_mesh   ) == src_primary.end())
        {
            it = src_secondary.erase(it);
            continue;
        }
        ++it;
    }

    //rtim dst secondary mesh vector
    for(std::vector<int>::const_iterator it = dst_secondary.begin();
        it != dst_secondary.end();
        true)
    {
        buf_primary_mesh = secondary_mesh_to_primary_mesh(*it);

        if(std::find(dst_primary.begin(),
                     dst_primary.end()  ,
                     buf_primary_mesh   ) == dst_primary.end())
        {
            it = dst_secondary.erase(it);
            continue;
        }
        ++it;
    }

    //w.i.p
}


void t_JMC::add_path(const std::list<cd::t_xy<int> >& _path)
{
    if(_path.size() < 2)
    {
        return;
    }

    std::map<int, std::vector< std::list< cd::t_xy<int> > > > buf_path_map;

    std::list< cd::t_xy<int> >::const_iterator it_before =  _path.begin();
    std::vector<int> buf_primary_mesh_before;

    std::vector<int> buf_primary_mesh;

    for(std::list< cd::t_xy<int> >::const_iterator it = ++_path.begin();
        it != _path.end();
        ++it)
    {
        buf_primary_mesh = location_to_primary_mesh(*it);
        for(unsigned int i = 0; i < buf_primary_mesh.size(); ++i)
        {
            if(buf_path_map.count(buf_primary_mesh.at(i)) == 0)
            {
                buf_path_map.insert
                    (std::make_pair(buf_primary_mesh.at(i)      ,
                                    std::vector< 
                                        std::list< cd::t_xy<int> > >()));
            }

            if(std::find(buf_primary_mesh_before.begin(),
                         buf_primary_mesh_before.end()  ,
                         buf_primary_mesh.at(i)         ) ==
               buf_primary_mesh_before.end()                )
            {
                buf_path_map[buf_primary_mesh.at(i)].
                    push_back(std::list< cd::t_xy<int> >());
            }

            buf_path_map[buf_primary_mesh.at(i)].
                back().
                push_back(cd::t_xy<int>(*it));
        }

        buf_primary_mesh_before = buf_primary_mesh;
    }

    for(std::map<int, std::vector< std::list< cd::t_xy<int> > > >::iterator it
            = buf_path_map.begin();
        it != buf_path_map.end();
        ++it)
    {
        for(std::vector< std::list< cd::t_xy<int> > >::iterator it_path =
                it->second.begin();
            it_path != it->second.end();
            ++it_path)
        {
            if(it_path->size() < 2)
            {
                continue;
            }

            if(m_primary_mesh.count(it->first) == 0)
            {
                m_primary_mesh[it->first] = t_primary_mesh(it->first);
            }

            m_primary_mesh[it->first].add_path(*it_path);
        }
    }
}


void
t_JMC::deep_copy
    (const t_JMC& _origin)
{
    m_primary_mesh.clear();

    for(std::map<int, t_primary_mesh>::const_iterator it
            = _origin.m_primary_mesh.begin();
        it != _origin.m_primary_mesh.end();
        ++it)
    {
        m_primary_mesh[it->first] = t_primary_mesh(it->second);
    }
}


std::vector< std::list<cd::t_xy<int> > >
t_JMC::get_path_array
    (const cd::t_p_graph&             _graph              ,
     const unsigned int               _node_num           ,
     const std::list<cd::t_xy<int> >& _processed_path_list)
        const
{
    std::vector< std::list< cd::t_xy<int> > > result = 
        {
            std::list< cd::t_xy<int> >(_processed_path_list)
        };

    std::vector< std::list< cd::t_xy<int> > > buf_v_l_xy;

    std::list< cd::t_xy<int> > buf_l_xy;

    for(unsigned int index = _node_num              ;
        true;
        index = _graph.m_adjacency.at(index).front())
    {
        result.front().
            push_back(cd::t_xy<int>
            (_graph.m_node_location.at(index)));

        if(_graph.m_adjacency.at(index).empty())
        {
            break;
        }

        buf_l_xy = result.front();
        for(size_t s = 1; s < _graph.m_adjacency.at(index).size(); ++s)
        {
            buf_v_l_xy = get_path_array(_graph                            ,
                                        _graph.m_adjacency.at(index).at(s),
                                        buf_l_xy                          );

            for(std::vector< std::list< cd::t_xy<int> > >::iterator it =
                    buf_v_l_xy.begin();
                it != buf_v_l_xy.end();
                ++it)
            {
                result.push_back(std::list< cd::t_xy<int> >(*it));
            }
        }
    }

    return result;
}


}