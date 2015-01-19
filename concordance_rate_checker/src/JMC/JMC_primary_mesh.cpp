#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

#include "../log/log.hpp"

namespace jmc
{
t_primary_mesh::t_primary_mesh()
{
    m_mesh_number    = 0;
    m_secondary_mesh = std::map<int, t_secondary_mesh >();
}


t_primary_mesh::t_primary_mesh(const t_primary_mesh& _origin)
{
    m_mesh_number    = _origin.m_mesh_number;

    m_secondary_mesh.clear();
    
    for(std::map<int, t_secondary_mesh>::const_iterator it
        = _origin.m_secondary_mesh.begin();
        it != _origin.m_secondary_mesh.end();
        ++it)
    {
        m_secondary_mesh[it->first] = t_secondary_mesh(it->second, *this);
    }
}


t_primary_mesh::t_primary_mesh(const int _mesh_number)
{
    m_mesh_number    = _mesh_number;
    m_secondary_mesh = std::map<int, t_secondary_mesh >();
}


t_primary_mesh::~t_primary_mesh()
{
}


t_primary_mesh& t_primary_mesh::operator=(const t_primary_mesh& _rhs)
{
    m_mesh_number    = _rhs.m_mesh_number;
    m_secondary_mesh.clear();
    
    for(std::map<int, t_secondary_mesh>::const_iterator it
        = _rhs.m_secondary_mesh.begin();
        it != _rhs.m_secondary_mesh.end();
        ++it)
    {
        m_secondary_mesh[it->first] = t_secondary_mesh(it->second, *this);
    }

    return *this;
}


void t_primary_mesh::add_path(const std::list< cd::t_xy<int> >& _path)
{
    std::map<int, std::vector< std::list< cd::t_xy<int> > > > buf_path;

    std::vector<int> before_added_secondary_mesh_num;

    std::vector<int> buf_secondary_mesh;
    
    for(std::list< cd::t_xy<int> >::const_iterator it = _path.begin();
        it != _path.end();
        ++it)
    {
        buf_secondary_mesh = location_to_secondary_mesh(*it);

        for(unsigned int i = 0; i < buf_secondary_mesh.size(); ++i)
        {
            if(buf_secondary_mesh.at(i) / 100 != m_mesh_number)
            {
                continue;
            }

            if(buf_path.count(buf_secondary_mesh.at(i)) == 0)
            {
                buf_path[buf_secondary_mesh.at(i)]
                    = std::vector< std::list< cd::t_xy<int> > >();
            }
            if(std::find(before_added_secondary_mesh_num.begin(),
                         before_added_secondary_mesh_num.end()  ,
                         buf_secondary_mesh.at(i)               ) ==
               before_added_secondary_mesh_num.end()              )
            {
                buf_path[buf_secondary_mesh.at(i)].
                    push_back(std::list< cd::t_xy<int> >());
            }

            buf_path[buf_secondary_mesh.at(i)]
                .back().push_back(cd::t_xy<int>(*it));
        }

        before_added_secondary_mesh_num = buf_secondary_mesh;
    }

    for(std::map<int, std::vector< std::list< cd::t_xy<int> > > >::iterator it
            = buf_path.begin();
        it != buf_path.end();
        ++it)
    {
        if(it->second.empty())
        {
            continue;
        }

        
        if(m_secondary_mesh.count(it->first) == 0)
        {
            m_secondary_mesh.insert
                (std::make_pair(it->first                         , 
                                t_secondary_mesh(*this, it->first)));
            m_secondary_mesh[it->first].add_outline();

            
        }

        for(std::vector< std::list< cd::t_xy<int> > >::iterator it_path
                = it->second.begin();
            it_path != it->second.end();
            ++it_path)
        {
            m_secondary_mesh[it->first].add_path(*it_path);
        }
    }

    return;
}


std::string t_primary_mesh::to_string() const
{
    io::t_log::get_instance().write_line("write : " +
                                         std::to_string(m_mesh_number));

    std::string result = "";
    for(std::map<int, t_secondary_mesh>::const_iterator it
        = m_secondary_mesh.begin();
        it != m_secondary_mesh.end();
        ++it)
    {
        result += it->second.to_string();
    }

    return result;
}


}