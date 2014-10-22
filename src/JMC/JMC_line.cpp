#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

#include "../log/log.hpp"

namespace jmc
{


t_line::t_line()
{
    m_series_number = 0;
    m_coordinate = std::vector<cd::t_xy<int>* >();

    m_invoker = nullptr;
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

    m_invoker = nullptr;
}

t_line::t_line(t_layer*                         _invoker        ,
               const unsigned int               _series_number  ,
               const std::list< cd::t_xy<int> > _coordinate_list)
{
    m_series_number = _series_number;
    m_coordinate    = std::vector< cd::t_xy<int>* >();
    m_invoker = _invoker;

    cd::t_xy<int> buffer_xy_int;
    for(std::list< cd::t_xy<int> >::const_iterator it
            = _coordinate_list.begin();
        it != _coordinate_list.end();
        ++it)
    {
        buffer_xy_int = encode_coordinate
                            (*it,
                             m_invoker->m_invoker->m_mesh_number);
        m_coordinate.push_back(new cd::t_xy<int>(buffer_xy_int));
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

    m_invoker = _rhs.m_invoker;

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


bool t_line::do_intention_coordinate(const std::list< cd::t_xy<int> > _target)
    const
{
    std::list< cd::t_xy<int> >::const_iterator target_it;
    target_it = _target.begin();
    std::vector< cd::t_xy<int>* >::const_iterator recode_it;
    recode_it = m_coordinate.begin();

    cd::t_xy<int> buf_xy_int;

    while(true)
    {
        if(target_it == _target.end() || recode_it == m_coordinate.end())
        {
            return false;
        }
        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker->m_invoker->m_mesh_number);

        if(buf_xy_int == **recode_it)
        {
            break;
        }

        ++recode_it;
    }

    while(target_it == _target.end())
    {
        if(recode_it == m_coordinate.end())
        {
            return false;
        }

        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker->m_invoker->m_mesh_number);

        if(buf_xy_int != **recode_it)
        {
            return false;
        }

        ++target_it;
        ++recode_it;
    }

    return true;
}


bool t_line::is_intentioned_coordinate
                (const std::list< cd::t_xy<int> > _target)
    const
{
    std::list< cd::t_xy<int> >::const_iterator target_it;
    target_it = _target.begin();
    std::vector< cd::t_xy<int>* >::const_iterator recode_it;
    recode_it = m_coordinate.begin();

    cd::t_xy<int> buf_xy_int;

    while(true)
    {
        if(target_it == _target.end() || recode_it == m_coordinate.end())
        {
            return false;
        }

        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker->m_invoker->m_mesh_number);

        if(buf_xy_int == **recode_it)
        {
            break;
        }

        ++target_it;
    }

    while(recode_it == m_coordinate.end())
    {
        if(target_it == _target.end())
        {
            return false;
        }

        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker->m_invoker->m_mesh_number);

        if(buf_xy_int != **recode_it)
        {
            return false;
        }

        ++target_it;
        ++recode_it;
    }

    return true;

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
    std::string result = "";
    char buf_line[RECODE_LENGTH + 1] = "";
    
    memset(buf_line, ' ', RECODE_LENGTH);

    /* sprintf_s(dest, format,
     *         layer code, data item code, line series number, line type code, 
     *         dst. node number, dst. adj. info,
     *         src. node number, src. adj. info,
     *         left-side administratively code,
     *         right-side administratively code,
     *         num. of coordinate, space
     */
    sprintf_s(buf_line,
              "L %2d%2d%5u%6u%5u%1u%5u%1u          %6u                           ",
            2, 2, m_series_number, 0, 0, 0, 0, 0, 
            get_num_of_coordinate());

    result += buf_line;
    result += "\n";

    int counter_writerd_coordinate = 0;
    char buf_coordinate[11] = "";

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
        for(true; counter_writerd_coordinate < 7; ++counter_writerd_coordinate)
        {
            result += "          ";
        }
        result += "  \n";
    }

    return result;
}


}