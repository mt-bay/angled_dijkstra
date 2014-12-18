#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"
#include "../log/log.hpp"
#include "../tools/define.hpp"

namespace jmc
{


t_secondary_mesh::t_secondary_mesh()
    : m_invoker(t_primary_mesh())
{
    m_mesh_number = 0;
    m_layer = std::vector< t_layer >();
}


t_secondary_mesh::t_secondary_mesh(const t_secondary_mesh& _origin)
    : m_invoker(_origin.m_invoker)
{
    m_mesh_number = _origin.m_mesh_number;

    m_layer = std::vector< t_layer >();
    m_layer.clear();

    for(std::vector< t_layer >::iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        m_layer.push_back(t_layer(*it, *this));
    }
}


t_secondary_mesh::t_secondary_mesh
    (const t_secondary_mesh& _origin,
     t_primary_mesh&   _invoker)
     : m_invoker(_invoker)
{
    m_mesh_number = _origin.m_mesh_number;

    m_layer.clear();

    for(std::vector< t_layer >::iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        m_layer.push_back(t_layer(*it, *this));
    }
}


t_secondary_mesh::t_secondary_mesh(t_primary_mesh& _invoker,
                                   const int _secondary_mesh_number)
    : m_invoker(_invoker)
{
    m_mesh_number = _secondary_mesh_number;
    m_layer = std::vector< t_layer >();

    m_invoker = _invoker;
}


t_secondary_mesh::~t_secondary_mesh()
{

}


t_secondary_mesh& t_secondary_mesh::operator= (const t_secondary_mesh& _rhs)
{
    m_invoker = _rhs.m_invoker;

    m_mesh_number = _rhs.m_mesh_number;

    m_layer.clear();

    for(std::vector< t_layer >::const_iterator it = _rhs.m_layer.begin();
        it != _rhs.m_layer.end();
        ++it)
    {
        m_layer.push_back(t_layer(*it));
    }

    return *this;
}


void t_secondary_mesh::add_layer_recode(const t_layer _target)
{
    m_layer.push_back(t_layer(_target));
}


void t_secondary_mesh::add_outline()
{
    int found = find_last_layer_index(t_layer::code_type_e::ADMINISTRATIVE);
    if(found == -1)
    {
        m_layer.push_back(t_layer(t_layer::code_type_e::ADMINISTRATIVE, *this));
        found = find_last_layer_index(t_layer::code_type_e::ADMINISTRATIVE);
    }
    std::list< cd::t_xy<int> >& path = std::list< cd::t_xy<int> >
    {
        get_padding() + cd::t_xy<int>(10000,     0),
        get_padding() + cd::t_xy<int>(10000, 10000),
        get_padding() + cd::t_xy<int>(    0, 10000),
        get_padding() + cd::t_xy<int>(    0,     0),
        get_padding() + cd::t_xy<int>(10000,     0)
    };

    m_layer.back().add_path(9, 9, path);
}


void t_secondary_mesh::add_path(const std::list< cd::t_xy<int> >& _path)
{
    int found = find_last_layer_index(t_layer::code_type_e::ROAD);
    if(found == -1)
    {
        m_layer.push_back(t_layer(t_layer::code_type_e::ROAD, *this));
        found = find_last_layer_index(t_layer::code_type_e::ROAD);
    }

    m_layer.at(found).add_path(2, 0, _path);
    return;
}


int t_secondary_mesh::find_last_layer_index(short int _layer_code)
    const
{
    for(int i = m_layer.size() - 1; i >= 0; --i)
    {
        if(m_layer.at(i).m_code == _layer_code)
        {
            return i;
        }
    }
    return -1;
}


unsigned int t_secondary_mesh::get_num_of_line() const
{
    unsigned int result = 0;
    for(std::vector< t_layer >::const_iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        result += (*it).m_line.size();
    }

    return result;
}

unsigned int t_secondary_mesh::get_num_of_recode() const
{
    unsigned int result = 1;
    for(std::vector< t_layer >::const_iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        result += (*it).get_num_of_recode();
    }

    return result;
}


std::string t_secondary_mesh::to_string() const
{

    std::string result = "";
    char buf_line[RECODE_LENGTH + 1];
    memset(buf_line, ' ', RECODE_LENGTH);

    /* sprintf_s(dest, format,
     *         secondary mesh code, figure name, num. of layer, num. of node,
     *         num. of line, num. of area, num. of point, num. of recode,
     *         space)
     */
    sprintf_s(buf_line, "M %6u%10s%3u%5u%5u%5u%5u%5u                ",
            m_mesh_number, " ", m_layer.size(), 0, get_num_of_line(), 0, 0,
            get_num_of_recode());

    result += buf_line;
    result += "\n";

    for(std::vector< t_layer >::const_iterator it = m_layer.begin();
        it != m_layer.end();
        ++it)
    {
        result += (*it).to_string();
    }

    return result;
}


cd::t_xy<int> t_secondary_mesh::get_padding()
{
    return cd::t_xy<int>((((((m_mesh_number /   100) % 100)
                            * (SECONDARY_MESH_MAX + 1))
                        +    (m_mesh_number /     1) %  10))
                        * MESH_LOCATION_MAX_X            ,
                         (((((m_mesh_number / 10000) % 100)
                            * (SECONDARY_MESH_MAX + 1))
                        +    (m_mesh_number /    10) %  10))
                        * MESH_LOCATION_MAX_Y);
}


}