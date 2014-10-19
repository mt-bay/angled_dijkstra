#include "JMC.hpp"

namespace jmc
{

t_layer::t_layer()
{

}


t_layer::t_layer(const t_layer& _origin)
{
    m_line = std::vector< t_line* >();

    for(std::vector< t_line* >::const_iterator it = _origin.m_line.begin();
        it != _origin.m_line.end();
        ++it)
    {
        m_line.push_back(new t_line(**it));
    }
    
}


t_layer::~t_layer()
{
    for(std::vector< t_line* >::iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        delete *it;
    }
}


t_layer& t_layer::operator=(const t_layer& _rhs)
{
    for(std::vector< t_line* >::iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        delete *it;
    }
    m_line.clear();

    for(std::vector< t_line* >::const_iterator it = _rhs.m_line.begin();
        it != _rhs.m_line.end();
        ++it)
    {
        m_line.push_back(new t_line(**it));
    }

    return *this;
}


void t_layer::add_line_record(const t_line _target)
{
    m_line.push_back(new t_line(_target));
}


}