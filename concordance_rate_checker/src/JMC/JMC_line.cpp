#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

#include "../log/log.hpp"

#include "../tools/tools.hpp"

namespace jmc
{


t_line::t_line()
    : m_invoker(t_layer())
{
    m_invoker = t_layer();

    m_series_number = 0;
    m_coordinate    = std::vector<cd::t_xy<int> >();
    m_code          = 0;
    m_type          = 0;
}


t_line::t_line(const t_line& _origin)
    : m_invoker(_origin.m_invoker)
{
    m_series_number = _origin.m_series_number;
    m_code          = _origin.m_code;
    m_type          = _origin.m_type;

    m_coordinate.clear();

    for(std::vector< cd::t_xy<int> >::const_iterator it
            = _origin.m_coordinate.begin();
        it != _origin.m_coordinate.end();
        ++it)
    {
        m_coordinate.push_back(cd::t_xy<int>(*it));
    }
}


t_line::t_line(const t_line& _origin, t_layer& _invoker)
    : m_invoker(_invoker)
{
    m_series_number = _origin.m_series_number;
    m_code          = _origin.m_code;
    m_type          = _origin.m_type;

    m_coordinate.clear();

    for(std::vector< cd::t_xy<int> >::const_iterator it
            = _origin.m_coordinate.begin();
        it != _origin.m_coordinate.end();
        ++it)
    {
        m_coordinate.push_back(cd::t_xy<int>(*it));
    }
}


t_line::t_line
    (t_layer&                       _invoker     ,
     const std::vector<std::string> _contents_str)
    : m_invoker(_invoker)
{
    m_code =
        std::stoi(mt::substr_byte(_contents_str.front(),  4, 2));
    m_series_number =
        std::stoi(mt::substr_byte(_contents_str.front(),  6, 5));
    m_type =
        std::stoi(mt::substr_byte(_contents_str.front(), 11, 6));

    size_t num_of_coordinate =
        std::stoi(mt::substr_byte(_contents_str.front(), 39, 6));

    size_t num_of_coordinate_recode =
        (num_of_coordinate - 1) / 7 + 1;

    cd::t_xy<int> buf_xy;

    for(size_t s = 0; s < num_of_coordinate_recode; ++s)
    {
        for(int i = 0; i < 7 || i < num_of_coordinate - (s * 7 + i); ++i)
        {


            buf_xy = 
                cd::t_xy<int>(
                    std::stoi(mt::substr_byte(_contents_str.at(s + 1),
                                              (i * 10)               ,
                                              (i + 10) + 5)          ),
                    std::stoi(mt::substr_byte(_contents_str.at(s + 1),
                                              (i * 10) + 5           ,
                                              (i + 10) + 5))         );
            m_coordinate.push_back(buf_xy);
        }
    }
}


t_line::t_line(t_layer&                          _invoker        ,
               const unsigned int                _series_number  ,
               const short int                   _code           ,
               const short int                   _type           ,
               const std::list< cd::t_xy<int> >& _coordinate_list)
    : m_invoker(_invoker)
{
    m_series_number = _series_number;
    m_coordinate    = std::vector< cd::t_xy<int> >();
    m_code          = _code;
    m_type          = _type;

    cd::t_xy<int> buffer_xy_int;
    for(std::list< cd::t_xy<int> >::const_iterator it
            = _coordinate_list.begin();
        it != _coordinate_list.end();
        ++it)
    {
        buffer_xy_int = encode_coordinate
                            (*it,
                             m_invoker.m_invoker.m_mesh_number);
        m_coordinate.push_back(cd::t_xy<int>(buffer_xy_int));
    }
}


t_line::~t_line()
{

}


t_line& t_line::operator=(const t_line& _rhs)
{
    m_code = _rhs.m_code;
    
    m_coordinate.clear();
    
    for(std::vector< cd::t_xy<int> >::const_iterator it
            = _rhs.m_coordinate.begin();
        it != _rhs.m_coordinate.end();
        ++it)
    {
        m_coordinate.push_back(cd::t_xy<int>(*it));
    }

    m_invoker = _rhs.m_invoker;

    return *this;
}


void t_line::add_coordinate(const cd::t_xy<int> _coordinate)
{
    cd::t_xy<int> buf_xy_int;
    buf_xy_int = encode_coordinate(_coordinate,
                                   m_invoker.m_invoker.m_mesh_number);
    m_coordinate.push_back(cd::t_xy<int>(buf_xy_int));
}


void t_line::renewal_coordinate_list(const std::list< cd::t_xy<int> > _coordinate)
{
    m_coordinate.clear();

    cd::t_xy<int> buf_xy_int;

    for(std::list< cd::t_xy<int> >::const_iterator it = _coordinate.begin();
        it != _coordinate.end();
        ++it)
    {
        buf_xy_int = encode_coordinate(*it,
                                       m_invoker.m_invoker.m_mesh_number);
        m_coordinate.push_back(cd::t_xy<int>(buf_xy_int));
    }
}


bool t_line::do_intention_coordinate(const std::list< cd::t_xy<int> > _target)
    const
{
    std::list< cd::t_xy<int> >::const_iterator target_it;
    target_it = _target.begin();
    std::vector< cd::t_xy<int> >::const_iterator recode_it;
    recode_it = m_coordinate.begin();

    cd::t_xy<int> buf_xy_int;

    while(true)
    {
        if(target_it == _target.end() || recode_it == m_coordinate.end())
        {
            return false;
        }
        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker.m_invoker.m_mesh_number);

        if(buf_xy_int == *recode_it)
        {
            break;
        }

        ++recode_it;
    }

    while(target_it != _target.end())
    {
        if(recode_it == m_coordinate.end())
        {
            return false;
        }

        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker.m_invoker.m_mesh_number);

        if(buf_xy_int != *recode_it)
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
    std::vector< cd::t_xy<int> >::const_iterator recode_it;
    recode_it = m_coordinate.begin();

    cd::t_xy<int> buf_xy_int;

    while(true)
    {
        if(target_it == _target.end() || recode_it == m_coordinate.end())
        {
            return false;
        }

        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker.m_invoker.m_mesh_number);

        if(buf_xy_int == *recode_it)
        {
            break;
        }

        ++target_it;
    }

    while(recode_it != m_coordinate.end())
    {
        if(target_it == _target.end())
        {
            return false;
        }

        buf_xy_int = encode_coordinate(*target_it,
                                       m_invoker.m_invoker.m_mesh_number);

        if(buf_xy_int != *recode_it)
        {
            return false;
        }

        ++target_it;
        ++recode_it;
    }

    return true;

}


bool t_line::starting_point_is_outline_connected()
    const
{
    if(m_coordinate.size() <= 0)
    {
        return false;
    }

    if(m_coordinate.front().x ==     0 ||
       m_coordinate.front().x == 10000 ||
       m_coordinate.front().y ==     0 ||
       m_coordinate.front().y == 10000)
    {
        return true;
    }
    return false;
}


bool t_line::end_point_is_outline_connected()
    const
{
    if(m_coordinate.size() <= 0)
    {
        return false;
    }

    if(m_coordinate.back ().x ==     0 ||
       m_coordinate.back ().x == 10000 ||
       m_coordinate.back ().y ==     0 ||
       m_coordinate.back ().y == 10000)
    {
        return true;
    }

    return false;
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


std::string t_line::to_string(/*const t_layer* _invoker*/) const
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
            (short int)m_invoker.m_code, m_code, m_series_number, m_type,
            get_num_of_coordinate(), ((starting_point_is_outline_connected())? 2 : 0),
            0, ((end_point_is_outline_connected())?      2 : 0), 
            get_num_of_coordinate());

    result += buf_line;
    result += "\n";

    int counter_writerd_coordinate = 0;
    char buf_coordinate[11] = "";

    //coordinate recode
    for(unsigned int i = 0; i < m_coordinate.size(); ++i)
    {
        sprintf_s(buf_coordinate, "%5d%5d",
                m_coordinate.at(i).x, m_coordinate.at(i).y);
        result += buf_coordinate;
        if(++counter_writerd_coordinate % 7 == 0)
        {
            result += "  \n";
        }
    }
    if(counter_writerd_coordinate % 7 != 0)
    {
        for(true                               ; 
            counter_writerd_coordinate % 7 != 0;
            ++counter_writerd_coordinate       )
        {
            result += "          ";
        }
        result += "  \n";
    }

    return result;
}


}