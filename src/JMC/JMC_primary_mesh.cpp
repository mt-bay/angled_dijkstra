#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

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
    std::map<int, std::list< cd::t_xy<int> > > buf_path;

    int buf_secondary_mesh;

    
    for(std::list< cd::t_xy<int> >::const_iterator it = _path.begin();
        it != _path.end();
        ++it)
    {
        buf_secondary_mesh = location_to_secondary_mesh(*it);

        if(buf_path.count(buf_secondary_mesh) == 0)
        {
            buf_path[buf_secondary_mesh] = std::list< cd::t_xy<int> >();
        }
        buf_path[buf_secondary_mesh].push_back(cd::t_xy<int>(*it));
    }

    for(std::map<int, std::list< cd::t_xy<int> > >::iterator it
            = buf_path.begin();
        it != buf_path.end();
        ++it)
    {
        if(m_secondary_mesh.count(it->first) == 0)
        {
            m_secondary_mesh[it->first] = new t_secondary_mesh();
        }

        m_secondary_mesh[it->first]->add_path(it->second);
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