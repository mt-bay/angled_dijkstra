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


void t_secondary_mesh::add_path(const std::list< cd::t_xy<int> >& _path)
{
    m_layer.push_back(new t_layer());
    m_layer.at(m_layer.size() - 1)->add_path(_path);

    return;
}


void t_secondary_mesh::add_layer_recode(const t_layer _target)
{
    m_layer.push_back(new t_layer(_target));
}


unsigned int t_secondary_mesh::get_num_of_line() const
{
    unsigned int result = 0;
    for(std::vector< t_layer* >::const_iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        result += (*it)->m_line.size();
    }

    return result;
}

unsigned int t_secondary_mesh::get_num_of_recode() const
{
    unsigned int result = 1;
    for(std::vector< t_layer* >::const_iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        result += (*it)->get_num_of_recode();
    }

    return result;
}


std::string t_secondary_mesh::to_string() const
{
    std::string result = "";
    char buf_line[72];

    /* sprintf_s(dest, format,
     *         secondary mesh code, figure name, num. of layer, num. of node,
     *         num. of line, num. of area, num. of point, num. of recode,
     *         space)
     */
    sprintf_s(buf_line, "M %6u%10s%3u%5u%5u%5u%5u%5u%16s",
            m_mesh_number, " ", m_layer.size(), 0, get_num_of_line(), 0, 0,
            get_num_of_recode()," ");

    for(std::vector< t_layer* >::const_iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        result += (*it)->to_string();
    }

    return result;
}


}