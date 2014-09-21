#pragma once


#include <string>


namespace jmc
{

enum layer_code_e : int
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
enum recode_type_e
{
    M ,
    H1,
    H2,
};


class header_t
{
    /* member value and instance */
public:
    recode_type_e m_recode_type;
};

class mesh_header_t : public header_t
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


class layer_header_t : public header_t
{
    /* member value and instance */
public:
    layer_code_e m_layer_code;
    unsigned int m_node_num;
    unsigned int m_line_num;
    unsigned int m_area_num;
    unsigned int m_point_num;

    std::string  m_first_creation_date;
    std::string  m_last_updated_date;
};



}