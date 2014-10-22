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
     * parameter : invoker, secondary mesh number
     */
    t_secondary_mesh(t_primary_mesh* _invoker,
                     const int _secondary_mesh_number);


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
    t_primary_mesh* m_invoker;
    int m_mesh_number;

private:
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
     * invoker setter constructor
     * parameter : invoker
     */
    t_layer(t_secondary_mesh* _invoker);

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
    t_secondary_mesh* m_invoker;
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
    t_line(t_layer*                         _invoker        ,
           const unsigned int               _series_number  ,
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
    void renewal_coordinate_list
            (const std::list< cd::t_xy<int> > _coordinate_list);

    /* 
     * do this coordinate recode intention argv?
     * parameter    : coordinate list
     * return value : is this coordinate recode intention argv?
     * exception    : none
     */
    bool do_intention_coordinate(const std::list< cd::t_xy<int> > _target) 
        const;

    /* 
     * is argv intention this coordinate recode?
     * parameter    : coordinate list
     * return value : is argv intention coordinate recode?
     * exception    : none
     */
    bool is_intentioned_coordinate(const std::list< cd::t_xy<int> > _target)
        const;

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
     * get src. node number
     * parameter    : void
     * return value : src. node number
     * exception    : none
     */
    unsigned int get_src_node_number() const;

    /* 
     * get dst. node nuber
     * parameter    : void
     * return value : dst. node number
     * exception    : none
     */
    unsigned int get_dst_node_number() const;

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
    t_layer* m_invoker;
private:
};

/* function */
std::vector<int> location_to_primary_mesh
                    (const cd::t_xy<int> _source);
std::vector<int> location_to_secondary_mesh
                    (const cd::t_xy<int> _source);

cd::t_xy<int> encode_coordinate(const cd::t_xy<int> _source        ,
                                const int           _secondary_mesh);

/* constant */
const int RECODE_LENGTH = 72;

}