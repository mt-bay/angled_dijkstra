#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

namespace jmc
{
t_primary_mesh::t_primary_mesh()
{
    m_mesh_number = 0;
    m_secondary_mesh = std::map<int, t_secondary_mesh*>();
}


t_primary_mesh::t_primary_mesh(const t_primary_mesh& _origin)
{
    m_mesh_number    = _origin.m_mesh_number;

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
    m_mesh_number    = _rhs.m_mesh_number;

    m_secondary_mesh = std::map<int, t_secondary_mesh*>();
    
    for(std::map<int, t_secondary_mesh*>::const_iterator it
        = _rhs.m_secondary_mesh.begin();
        it != _rhs.m_secondary_mesh.end();
        ++it)
    {
        m_secondary_mesh[it->first] = new t_secondary_mesh(*it->second);
    }
}


void t_primary_mesh::add_road_path(const std::list< cd::t_xy<int> > _road)
{
    std::map<int, 
        std::map<int, std::list< cd::t_xy<int> > > > buf_road;
    int buf_primary_mesh;
    int buf_secondary_mesh;


    for(std::list< cd::t_xy<int> >::const_iterator it = _road.begin();
        it != _road.end();
        ++it)
    {
        buf_primary_mesh = location_to_primary_mesh(*it);
        buf_secondary_mesh = location_to_secondary_mesh(*it);
        
        if(buf_road.count(buf_primary_mesh) == 0)
        {
            buf_road[buf_primary_mesh]
                = std::map<int, std::list< cd::t_xy<int> > >();
        }
        if(buf_road[buf_primary_mesh].count(buf_secondary_mesh) == 0)
        {
            buf_road[buf_primary_mesh][buf_secondary_mesh]
                = std::list< cd::t_xy<int> >();
        }
        buf_road[buf_primary_mesh][buf_secondary_mesh]
            .push_back(cd::t_xy<int>(*it));
    }
}


}