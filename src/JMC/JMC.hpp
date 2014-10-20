#pragma once


#include <vector>
#include <list>
#include <map>


namespace cd
{
template<typename T>
class t_xy;
}
namespace di
{
class t_dijkstra;
}


namespace jmc
{
class t_primary_mesh;
class t_secondary_mesh;
class t_layer;

class t_line;


/* class to output JMC file(s) */
class t_JMC
{
    /* constructor */
public :
    /* 
     * default constructor
     * parameter : void
     */
    t_JMC();

    /* 
     * dijkstra result to JMC instance
     * parameter : dijkstra result
     */
    t_JMC(const di::t_dijkstra& _dijkstra);

private:
    
    /* destructor */
public :
    virtual ~t_JMC();

    /* static method */
public :
private:

    /* method */
public :
    /* 
     * output jmc
     * parameter    : output directory
     * return value : write successful
     * exception    : none
     */
    bool output(const std::string _output_directory) const;

private:
    /* 
     * add path
     * parameter    : adding path
     * return value : void
     * exception    : none
     */
    void add_path(const std::list<cd::t_xy<int> >& _path);


    /* member variable and instance */
public :
    std::map<int, t_primary_mesh* > m_primary_mesh;

private:

};

/* primary mesh class */
class t_primary_mesh
{
    /* constructor and destructor */
public :
    /* 
     * default constructor
     * parameter : void
     */
    t_primary_mesh();

    /* 
     * copy constructor
     * parameter : origin
     */
    t_primary_mesh(const t_primary_mesh& _origin);

    /* 
     */

    /* 
     * destructor
     */
    virtual ~t_primary_mesh();
private:


    /* operator overload */
public:
    /* 
     * assignment operator
     * assign rhs instance to this instance
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_primary_mesh& operator= (const t_primary_mesh& _rhs);


    /* method */
public :
    /* 
     * add road path
     * parameter    : path
     * return value : void
     * exception    : none
     */
    void add_path(const std::list< cd::t_xy<int> >& _path);

    /* 
     * this instance to string
     * parameter    : void
     * return value : this instance to string
     * exception    : none
     */
    std::string to_string() const;


private:

    /* member variable and instance */
public:
    int m_mesh_number;
    std::map<int, t_secondary_mesh*> m_secondary_mesh;
};


/* secondary mesh recode class */
class t_secondary_mesh
{
    /* constructor and destructor */
public :
    /* 
     * default constructor
     * parameter : void
     */
    t_secondary_mesh();

    /* 
     * copy constructor
     * parameter : origin
     */
    t_secondary_mesh(const t_secondary_mesh& _origin);


    /* 
     * setter constructor
     * parameter : secondary mesh number
     */
    t_secondary_mesh(const int _secondary_mesh_number);


    /* 
     * destructor
     */
    ~t_secondary_mesh();


    /* operator overload */
public:
    /* 
     * assignment operator
     * assign rhs instance to this instance
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_secondary_mesh& operator= (const t_secondary_mesh& _rhs);


    /* method */
    /* 
     * add path
     * parameter    : adding path
     * return value : void
     * exception    : none
     */
    void add_path(const std::list< cd::t_xy<int> >& _path);

    /* 
     * add layer recode
     * parameter    : adding layer recode
     * return value : void
     * exception    : none
     */
    void add_layer_recode(const t_layer _target);

    /* 
     * get num. of line
     * parameter    : void
     * return value : num. of line
     * exception    : none
     */
    unsigned int get_num_of_line() const;

    /* 
     * get num. of recode
     * parameter    : void
     * return value : num. of recode
     * exception    : none
     */
    unsigned int get_num_of_recode() const;

    /* 
     * this instance to string
     * parameter    : void
     * return value : this instance to string
     * exception    : none
     */
    std::string to_string() const;


    /* member variable and instance */
public:
    std::vector< t_layer* > m_layer;

private:
    int m_mesh_number;
};


/* layer recode class */
class t_layer
{
    /* constructor and destructor */
public :
    /* 
     * default constructor
     * parameter : void
     */
    t_layer();

    /* 
     * copy constructor
     * parameter : origin
     */
    t_layer(const t_layer& _origin);

    /* 
     * destructor
     */
    ~t_layer();

    /* operator overload */
public:
    /* 
     * assignment operator
     * assign rhs instance to this instance
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_layer& operator= (const t_layer& _rhs);


    /* method */
    /* 
     * add path
     * parameter    : adding path
     * return value : void
     * exception    : none
     */
    void add_path(const std::list< cd::t_xy<int> >& _path);

    /* 
     * add line record
     * parameter    : adding line record
     * return value : void
     * exception    : none
     */
    void add_line_record(const t_line _target);

    /* 
     * get num of recode
     * parameter    : void
     * return value : num. of recode
     * exception    : none
     */
    unsigned int get_num_of_recode() const;

    /* 
     * this instance to string
     * parameter    : void
     * return value : this instance to string
     * exception    : none
     */
    std::string to_string() const;


    /* member variable and instance */
public:
    std::vector< t_line* > m_line;
};

/* line recode class */
class t_line
{
    /* constructor and destructor */
public :
    /* 
     * default construcor
     * parameter : void
     */
    t_line();

    /* 
     * copy constructor
     * parameter : origin
     */
    t_line(const t_line& _origin);

    /* 
     * coordinate setter constructor
     * parameter : coordinate list
     */
    t_line(const unsigned int               _series_number  ,
           const std::list< cd::t_xy<int> > _coordinate_list);

    /* 
     * destructor
     */
    ~t_line();

    /* operator overload */
public:
    /* 
     * assignment operator
     * assign rhs instance to this instance
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_line& operator= (const t_line& _rhs);


    /* method */
public :
    /* 
     * add coordinate
     * parameter    : coordinate
     * return value : void
     * exception    : none
     */
    void add_coordinate(const cd::t_xy<int> _coordinate);

    /* 
     * add coordinate list
     * parameter    : coordinate list
     * return value : void
     * exception    : none
     */
    void add_coordinate_list
            (const std::list< cd::t_xy<int> > _coordinate_list);

    /* 
     * get num. of line
     * parameter    : void
     * return value : num. of coordinate
     * exception    : none
     */
    unsigned int get_num_of_coordinate() const;

    /* 
     * get num. of recode
     * parameter    : void
     * return value : num. of recode
     * exception    : none
     */
    unsigned int get_num_of_recode() const;

    /* 
     * this instance to string
     * parameter    : void
     * return value : this instance to string
     * exception    : none
     */
    std::string to_string() const;


    /* member variable and instance */
public:
    unsigned int                  m_series_number;
    std::vector< cd::t_xy<int>* > m_coordinate;
};

/* function */
volatile int location_to_primary_mesh(const cd::t_xy<int>   _source);
volatile int location_to_secondary_mesh(const cd::t_xy<int> _source);
}