#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

#include "../log/log.hpp"

namespace jmc
{
t_primary_mesh::t_primary_mesh()
{
    m_secondary_mesh = std::map<int, t_secondary_mesh* >();
}


t_primary_mesh::t_primary_mesh(const t_primary_mesh& _origin)
{
    m_secondary_mesh = std::map<int, t_secondary_mesh*>();
    
    for(std::map<int, t_secondary_mesh*>::const_iterator it
        = _origin.m_secondary_mesh.begin();
        it != _origin.m_secondary_mesh.end();
        ++it)
    {
        m_secondary_mesh[it->first] = new t_secondary_mesh(*it->second);
    }
}


t_primary_mesh::~t_primary_mesh()
{
    std::map<int, t_secondary_mesh*>::iterator it;
    for(it =  m_secondary_mesh.begin();
        it != m_secondary_mesh.end();
        ++it                           )
    {
        delete it->second;
    }
}





t_primary_mesh& t_primary_mesh::operator=(const t_primary_mesh& _rhs)
{
    m_secondary_mesh = std::map<int, t_secondary_mesh*>();
    
    for(std::map<int, t_secondary_mesh*>::const_iterator it
        = _rhs.m_secondary_mesh.begin();
        it != _rhs.m_secondary_mesh.end();
        ++it)
    {
        m_secondary_mesh[it->first] = new t_secondary_mesh(*it->second);
    }
}


void t_primary_mesh::add_path(const std::list< cd::t_xy<int> >& _path)
{
    std::map<int, std::vector< std::list< cd::t_xy<int> > > > buf_path;

    std::vector<int> buf_secondary_mesh;
    
    for(std::list< cd::t_xy<int> >::const_iterator it = _path.begin();
        it != _path.end();
        ++it)
    {
        buf_secondary_mesh = location_to_secondary_mesh(*it);
        
        for(unsigned int i = 0; i < buf_secondary_mesh.size(); ++i)
        {
            if(buf_path.count(buf_secondary_mesh.at(i)) == 0)
            {
                buf_path[buf_secondary_mesh.at(i)]
                    .push_back(std::list< cd::t_xy<int> >());
                buf_path[buf_secondary_mesh.at(i)]
                    .at(buf_path[buf_secondary_mesh.at(i)].size() - 1)
                    = std::list< cd::t_xy<int> >();
            }
            if(buf_secondary_mesh.size() > 1)
            {
                for(std::map<int,
                        std::vector<
                            std::list< cd::t_xy<int> > > >::iterator it_path
                            = buf_path.begin();
                    it_path != buf_path.end();
                    ++it_path)
                {
                    it_path->second.push_back(std::list< cd::t_xy<int> >());
                }
            }

            buf_path[buf_secondary_mesh.at(i)]
                .at(buf_path[buf_secondary_mesh.at(i)].size() - 1)
                .push_back(cd::t_xy<int>(*it));
        }
    }

    for(std::map<int, std::vector< std::list< cd::t_xy<int> > > >::iterator
            it_map = buf_path.begin();
        it_map != buf_path.end();
        ++it_map)
    {
        for(std::vector< std::list< cd::t_xy<int> > >::iterator it_vec
                = it_map->second.begin();
            it_vec != it_map->second.end();
            true)
        {
            it_vec =(it_vec->size() < 2)?
                        it_map->second.erase(it_vec) : it_vec + 1;
        }
    }

    for(std::map<int, std::vector< std::list< cd::t_xy<int> > > >::iterator it
            = buf_path.begin();
        it != buf_path.end();
        ++it)
    {
        if(it->second.size() <= 0)
        {
            continue;
        }

        for(std::vector< std::list< cd::t_xy<int> > >::iterator it_path
                = it->second.begin();
            it_path != it->second.end();
            ++it_path)
        {
            if(m_secondary_mesh.count(it->first) == 0)
            {
                m_secondary_mesh[it->first] = new t_secondary_mesh
                                                (this, it->first);
            }

            m_secondary_mesh[it->first]->add_path(*it_path);
        }
    }

    return;
}


std::string t_primary_mesh::to_string() const
{
    std::string result = "";

    for(std::map<int, t_secondary_mesh* >::const_iterator it
        = m_secondary_mesh.begin();
        it != m_secondary_mesh.end();
        ++it)
    {
        result += it->second->to_string();
    }

    return result;
}


}