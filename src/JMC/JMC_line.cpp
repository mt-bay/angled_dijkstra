#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

namespace jmc
{


t_line::t_line()
{
    m_series_number = 0;
    m_coordinate = std::vector<cd::t_xy<int>* >();
}


t_line::t_line(const t_line& _origin)
{
    m_series_number = _origin.m_series_number;
    m_coordinate = std::vector<cd::t_xy<int>* >();

    for(std::vector< cd::t_xy<int>* >::const_iterator it
            = _origin.m_coordinate.begin();
        it != _origin.m_coordinate.end();
        ++it)
    {
        m_coordinate.push_back(new cd::t_xy<int>(**it));
    }

}

t_line::t_line(const unsigned int               _series_number  ,
               const std::list< cd::t_xy<int> > _coordinate_list)
{
    m_series_number = _series_number;
    m_coordinate    = std::vector< cd::t_xy<int>* >();

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


unsigned int t_line::get_num_of_coordinate() const
{
    return m_coordinate.size();
}


unsigned int t_line::get_num_of_recode() const
{
    unsigned int result = 1;
    result += ((m_coordinate.size() - 1) / 7) + 1;

    return result;
}


std::string t_line::to_string() const
{
    int counter_writerd_coordinate = 0;
    std::string result = "";
    char buf_line[72];
    char buf_coordinate[10];

    /* sprintf_s(dest, format,
     *         layer code, data item code, line series number, line type code, 
     *         dst. node number, dst. adj. info,
     *         src. node number, src. adj. info,
     *         left-side administratively code,
     *         right-side administratively code,
     *         num. of coordinate, space
     */
    sprintf_s(buf_line, "L %2d%2d%5u%6u%5u%1u%5u%1u%5u%5u%6u%27s",
            2, 2, m_series_number, 0, 0, 0, 0, 0, 0, 0,
            get_num_of_coordinate(), " ");

    for(unsigned int i = 0; i < m_coordinate.size(); ++i)
    {
        sprintf_s(buf_coordinate, "%5d%5d",
                m_coordinate.at(i)->x, m_coordinate.at(i)->y);
        result += buf_coordinate;
        if(++counter_writerd_coordinate % 7 == 0)
        {
            result += "  \n";
        }
    }
    if(counter_writerd_coordinate % 7 != 0)
    {
        result += "\n";
    }

    return result;
}


}