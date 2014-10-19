#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

namespace jmc
{


t_line::t_line()
{
    m_coordinate = std::vector<cd::t_xy<int>* >();
}


t_line::t_line(const t_line& _origin)
{
    m_coordinate = std::vector<cd::t_xy<int>* >();

    for(std::vector< cd::t_xy<int>* >::const_iterator it
            = _origin.m_coordinate.begin();
        it != _origin.m_coordinate.end();
        ++it)
    {
        m_coordinate.push_back(new cd::t_xy<int>(**it));
    }

}

t_line::t_line(const std::list< cd::t_xy<int> > _coordinate_list)
{
    m_coordinate = std::vector< cd::t_xy<int>* >();

    for(std::list< cd::t_xy<int> >::const_iterator it
        = _coordinate_list.begin();
        it != _coordinate_list.end();
        ++it)
    {
        m_coordinate.push_back(new cd::t_xy<int>(*it));
    }
}


t_line::~t_line()
{
    for(std::vector< cd::t_xy<int>* >::iterator it = m_coordinate.begin();
        it != m_coordinate.end();
        ++it)
    {
        delete *it;
    }
}


t_line& t_line::operator=(const t_line& _rhs)
{
    for(std::vector< cd::t_xy<int>* >::iterator it
            = m_coordinate.begin();
        it != m_coordinate.end();
        ++it)
    {
        delete *it;
    }
    m_coordinate.clear();
    
    for(std::vector< cd::t_xy<int>* >::const_iterator it
            = _rhs.m_coordinate.begin();
        it != _rhs.m_coordinate.end();
        ++it)
    {
        m_coordinate.push_back(new cd::t_xy<int>(**it));
    }

    return *this;
}


void t_line::add_coordinate(const cd::t_xy<int> _coordinate)
{
    m_coordinate.push_back(new cd::t_xy<int>(_coordinate));
}


void t_line::add_coordinate_list(const std::list< cd::t_xy<int> > _coordinate)
{
    for(std::list< cd::t_xy<int> >::const_iterator it = _coordinate.begin();
        it != _coordinate.end();
        ++it)
    {
        m_coordinate.push_back(new cd::t_xy<int>(*it));
    }
}


}