#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"


namespace jmc
{


t_secondary_mesh::t_secondary_mesh()
{
    m_mesh_number = 0;
    m_layer = std::vector< t_layer* >();
}


t_secondary_mesh::t_secondary_mesh(const t_secondary_mesh& _origin)
{
    m_mesh_number = _origin.m_mesh_number;

    for(std::vector< t_layer* >::iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        
    }
}

t_secondary_mesh::~t_secondary_mesh()
{
    for(std::vector< t_layer* >::iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        delete *it;
    }
}


t_secondary_mesh& t_secondary_mesh::operator= (const t_secondary_mesh& _rhs)
{
    m_mesh_number = _rhs.m_mesh_number;

    for(std::vector< t_layer* >::iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        delete *it;
    }
    m_layer.clear();

    for(std::vector< t_layer* >::const_iterator it = _rhs.m_layer.begin();
        it != _rhs.m_layer.end();
        ++it)
    {
        m_layer.push_back(new t_layer(**it));
    }

    return *this;
}


}