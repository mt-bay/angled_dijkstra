#include "JMC.hpp"

#include "../tools/tools.hpp"

#include "../coordinate/coordinate.hpp"

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


void t_layer::add_path(const std::list< cd::t_xy<int> >& _path)
{
    m_line.push_back(new t_line(m_line.size() + 1, _path));
}


void t_layer::add_line_record(const t_line _target)
{
    m_line.push_back(new t_line(_target));
}

unsigned int t_layer::get_num_of_recode() const
{
    unsigned int result = 1;
    for(std::vector< t_line* >::const_iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        result += (*it)->get_num_of_recode();
    }

    return result;
}


std::string t_layer::to_string() const
{
    std::string result = "";
    char buf_line[72];

    /* sprintf_s(dest, format, recode type, layer code,
     *         num. of node, num. of line, num. of area, num. of point,
     *         num. of recode, first creation date, last updated date, space
     */
    sprintf_s(buf_line, "%2s%2u%5u%5u%5u%5u%5u %4d %4d %33s",
            "H1", 2, 0, m_line.size(), 0, get_num_of_recode(),101,  101, " ");

    result += buf_line;

    for(std::vector< t_line* >::const_iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        result += (*it)->to_string();
    }

    return result;
}


}