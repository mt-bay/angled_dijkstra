#pragma once

#include <vector>
#include <string>


namespace cd
{
template<typename T>
class t_xy;
}

namespace jmc
{

enum e_layer_code : int
{
    ADMINISTRATIVE = 1,
    COASTLINE      = 1,
    ROAD           = 2,
    TRACK          = 3,
    RIVER          = 5,
    LAKE           = 5,
    SYMBOL         = 7,
    NOTE           = 7,
};

enum e_recode_type
{
    L ,
    M ,
    N ,
    H1,
    H2,
};

enum e_line_item_type : int
{
    //if(layer_code_e == 2)
    HIGHWAY                = 1,
    DRIVEWAY               = 1,
    NATIONAL_LOAD          = 2,
    LOCAL_LOAD             = 3,
    PREGECTURAL_LOAD       = 4,
    OTHER                  = 5,
};

enum e_line_type_code : int
{
    //if(layer_code_e == 2)
    ON_GROUND   = 1,
    UNDERGROUND = 2,
    TUNNEL      = 2,
};

enum e_connection_info : int
{
    IN_SEGMENT      = 0,
    ADJ_SEGMENT     = 1,
    NOT_ADJ_SEGMENT = 2,
};


class t_header
{
    /* member value and instance */
public:
    e_recode_type m_recode_type;
};

class t_mesh_header : public t_header
{
    /* member value and instance */
public:
    unsigned int m_mesh_code;
    std::string  m_diagram_name;
    unsigned int m_layer_num;
    unsigned int m_node_num;
    unsigned int m_line_num;
    unsigned int m_area_num;
    unsigned int m_point_num;
    unsigned int m_recode_num;
};


class t_layer_header : public t_header
{
    /* member value and instance */
public:
    e_layer_code m_layer_code;
    unsigned int m_node_num;
    unsigned int m_line_num;
    unsigned int m_area_num;
    unsigned int m_point_num;

    std::string  m_first_creation_date;
    std::string  m_last_updated_date;
};

class t_line_recode
{
    /* member value and instance */
public:
    e_recode_type     m_recode_type;
    e_layer_code      m_layer_type;
    e_line_item_type  m_item_type;
    unsigned int      m_number;
    e_line_type_code  m_line_type;
    int               m_src_node_number;
    e_connection_info m_src_info;
    int               m_dst_node_number;
    e_connection_info m_dst_info;
    int               m_left_admin_code;
    int               m_right_admin_code;
    std::vector< std::vector< cd::t_xy<long int>* > >
                      m_node;
};


class mesh_t
{
public:
    t_mesh_header header;
};

class layer_t
{
public:
    t_layer_header header;
};


const int secondary_mesh_num = 7;

}