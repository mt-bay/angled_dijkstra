#include "JMC.hpp"

#include "../tools/tools.hpp"

#include "../coordinate/coordinate.hpp"

#include "../log/log.hpp"

namespace jmc
{

t_layer::t_layer()
    : m_invoker(t_secondary_mesh())
{
    m_code = (t_layer::code_type_e)1;
    m_line = std::vector< t_line >();
}


t_layer::t_layer(const t_layer& _origin)
    : m_invoker(_origin.m_invoker)
{

    m_code = _origin.m_code;
    m_line.clear();

    for(std::vector< t_line >::const_iterator it = _origin.m_line.begin();
        it != _origin.m_line.end();
        ++it)
    {
        m_line.push_back(t_line(*it, *this));
    }
}


t_layer::t_layer(t_layer& _origin, t_secondary_mesh& _invoker)
    : m_invoker(_invoker)
{
    m_code = _origin.m_code;
    m_line.clear();

    for(std::vector< t_line >::const_iterator it = _origin.m_line.begin();
        it != _origin.m_line.end();
        ++it)
    {
        m_line.push_back(t_line(*it, *this));
    }
}


t_layer::t_layer(t_layer::code_type_e _layer_code,
                 t_secondary_mesh&    _invoker   )
    : m_invoker(_invoker)
{
    m_code = _layer_code;
    m_line = std::vector< t_line >();
}


t_layer::t_layer
    (t_secondary_mesh&              _invoker     ,
     const std::vector<std::string> _contents_str)
     : m_invoker(_invoker)
{
    std::vector<std::string> recode_str;

    std::string mesh_type_candidacy;

    for(std::vector<std::string>::const_iterator it =
            _contents_str.begin();
        it != _contents_str.end();
        ++it)
    {
        //node recode
        mesh_type_candidacy = mt::substr_byte(*it, 0, 2);
        if(mesh_type_candidacy == "N " ||
           mesh_type_candidacy == "L " ||
           mesh_type_candidacy == "A " ||
           mesh_type_candidacy == "P " )
        {
            push_recode(recode_str);
        }

        recode_str.push_back(*it);
    }
    //w.i.p
}


t_layer::~t_layer()
{

}


t_layer& t_layer::operator=(const t_layer& _rhs)
{
    m_invoker = _rhs.m_invoker;

    m_code = _rhs.m_code;

    m_line.clear();

    for(std::vector< t_line >::const_iterator it = _rhs.m_line.begin();
        it != _rhs.m_line.end();
        ++it)
    {
        m_line.push_back(t_line(*it));
    }

    return *this;
}


void t_layer::add_path(const short int                   _code,
                       const short int                   _type,
                       const std::list< cd::t_xy<int> >& _path)
{
    if(_path.size() < 2)
    {
        return;
    }
    for(std::vector< t_line >::iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        if(it->do_intention_coordinate(_path))
        {
            return;
        }
        if(it->is_intentioned_coordinate(_path))
        {
            it->renewal_coordinate_list(_path);
            return;
        }
    }
    
    m_line.push_back(t_line(*this, m_line.size() + 1, _code, _type, _path));
}


void t_layer::add_line_record(const t_line _target)
{
    m_line.push_back(t_line(_target));
}

unsigned int t_layer::get_num_of_recode() const
{
    unsigned int result = 1;
    for(std::vector< t_line >::const_iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        result += (*it).get_num_of_recode();
    }

    return result;
}


std::string t_layer::to_string() const
{
    std::string result = "";
    char buf_line[RECODE_LENGTH + 1] = "";
    memset(buf_line, ' ', RECODE_LENGTH);

    /* sprintf_s(dest, format, recode type, layer code,
     *         num. of node, num. of line, num. of area, num. of point,
     *         num. of recode, first creation date, last updated date, space
     */
    sprintf_s(buf_line, "%2s%2u%5u%5u%5u%5u%5u %04u %04u                                 ",
            "H1", (short int)m_code,
            m_node.size(), m_line.size(), m_area.size(), m_point.size(),
            get_num_of_recode(), 101,  101);

    result += buf_line;
    result += "\n";

    for(std::vector< t_line >::const_iterator it = m_line.begin();
        it != m_line.end();
        ++it)
    {
        result += it->to_string();
    }

    return result;
}

void t_layer::push_recode
    (const std::vector<std::string>& _content)
{
    if(_content.empty())
    {
        return;
    }

    std::string recode_type = mt::substr_byte(_content.front(), 0, 2);
    if(recode_type == "N ")
    {

    }
}


}