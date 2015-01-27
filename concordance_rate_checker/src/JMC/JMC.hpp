#pragma once


#include <vector>
#include <list>
#include <map>


namespace cd
{
template<typename T>
class t_xy;
class t_p_graph;
}


namespace jmc
{
class t_primary_mesh;
class t_secondary_mesh;
class t_layer;

class t_node;
class t_line;
class t_area;
class t_point;

/* class */
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
     * copy constructor
     * parameter : origin
     */
    t_JMC(const t_JMC& _origin);

    t_JMC(const cd::t_p_graph& _p_graph, unsigned int _src);

    /* 
     * construct by JMC file(s)
     * parameter : directory-path saved JMC file(s)
     */
    t_JMC(const std::string _jmc_dir);

private:
    
    /* destructor */
public :
    virtual ~t_JMC();

    /* operator overload */
    t_JMC& operator= (const t_JMC& _rhs);

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

    /* 
     * deep copy
     * parameter    : origin
     * return value : void
     * exception    : none
     */
    inline void deep_copy(const t_JMC& _origin);

    /* 
     * get path array
     * parameter    : graph, node number, next ref adj. number, path list
     * return value : path list
     */
    std::vector< std::list<cd::t_xy<int> > >
    get_path_array
        (const cd::t_p_graph&             _graph              ,
         const unsigned int               _node_num           ,
         const std::list<cd::t_xy<int> >& _processed_path_list
                                            = std::list< cd::t_xy<int> >())
            const;

    /* member variable and instance */
public :
    std::map<int, t_primary_mesh > m_primary_mesh;

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
     * mesh number setter constructor
     * parameter : mesh number
     */
    t_primary_mesh(int _mesh_number);

    /* 
     * read by primary mesh file
     * parameter : primary mesh file path
     */
    t_primary_mesh(const std::string _primary_mesh_path  ,
                   const int         _primary_mesh_number);

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
    std::map<int, t_secondary_mesh> m_secondary_mesh;
    int                             m_mesh_number;
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
     * copy and change invoker
     * parameter : origin, new invoker
     */
    t_secondary_mesh(const t_secondary_mesh& _origin,
                     t_primary_mesh&   _invoker);

    /* 
     * setter constructor
     * parameter : invoker, secondary mesh number
     */
    t_secondary_mesh(t_primary_mesh& _invoker,
                     const int _secondary_mesh_number);

    /* 
     * contents str to secondary mesh
     * parameter : invoker, contets str
     */
    t_secondary_mesh(t_primary_mesh&                 _invoker     ,
                     const std::vector<std::string>& _contents_str);

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
public:
    /* 
     * add layer recode
     * parameter    : adding layer recode
     * return value : void
     * exception    : none
     */
    void add_layer_recode(const t_layer _target);

    /* 
     * add outline
     * parameter    : none
     * return value : void
     * exception    : none
     */
    void add_outline();

    /* 
     * add path
     * parameter    : adding path
     * return value : void
     * exception    : none
     */
    void add_path(const std::list< cd::t_xy<int> >& _path);

    /* 
     * find last matched layer index
     * parameter    : layer code
     * return value : matched index
     * exception    : none
     */
    int find_last_layer_index(short int _layer_code)
        const;

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

private:
    cd::t_xy<int> get_padding();

    /* member variable and instance */
public:
    std::vector< t_layer > m_layer;
    t_primary_mesh&        m_invoker;
    int                    m_mesh_number;

private:
};


/* layer recode class */
class t_layer
{
    /* member enum */
public:
    enum code_type_e : short int
    {
        ADMINISTRATIVE = 1,
        ROAD           = 2,
        TRAIN          = 3,
        RIVER          = 5,
        NOTE           = 7,
    };

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
     * copy and change invoker
     * parameter : origin, invoker pointer
     */
    t_layer(t_layer& _origin, t_secondary_mesh& _invoker);

    /* 
     * invoker setter constructor
     * parameter : invoker
     */
    t_layer(code_type_e       _layer_code,
            t_secondary_mesh& _invoker   );

    /* 
     * contents str to layer
     * parameter : contents str
     */
    t_layer(t_secondary_mesh&              _invoker     ,
            const std::vector<std::string> _contents_str);

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
    void add_path(const short int                   _code,
                  const short int                   _type,
                  const std::list< cd::t_xy<int> >& _path);

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

private:
    void push_recode(const std::vector<std::string>& _content);

    /* member variable and instance */
public:
    code_type_e             m_code;

    std::vector< t_node >   m_node;
    std::vector< t_line >   m_line;
    std::vector< t_area >   m_area;
    std::vector< t_point >  m_point;

    t_secondary_mesh& m_invoker;
};

/* node recode class */
class t_node
{
public:
    /* constructor */
    t_node();

    t_node(const t_node& _origin);

    t_node(t_layer&                       _invoker     ,
           const std::vector<std::string> _contents_str);

    /* operator overload */
    t_node& operator= (const t_node& _rhs);
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
     * copy and change invoker
     * parameter : origin, invoker reference
     */
    t_line(const t_line& _origin, t_layer& _invoker);

    /* 
     * contents string to line recode
     * parameter : invoker
     */
    t_line(t_layer&                       _invoker     ,
           const std::vector<std::string> _contents_str);

    /* 
     * coordinate setter constructor
     * parameter : coordinate list
     */
    t_line(t_layer&                          _invoker        ,
           const unsigned int                _series_number  ,
           const short int                   _code           ,
           const short int                   _type           ,
           const std::list< cd::t_xy<int> >& _coordinate_list);

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
     * starting-point is outline-connected coordinate?
     * parameter    : void
     * return value : starting-point is outline-connected coordinate?
     * exception    : none
     */
    bool starting_point_is_outline_connected() const;

    /* 
     * end-point is outline-connected coordinate?
     * parameter    : void
     * return value : end-point is outline-connected coordinate?
     * exception    : none
     */
    bool end_point_is_outline_connected() const;

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
    std::string to_string(/*const t_layer* _invoker*/) const;

    /* member variable and instance */
public:
    short int                    m_code;
    unsigned int                 m_series_number;
    short int                    m_type;

    std::vector< cd::t_xy<int> > m_coordinate;
    t_layer&                     m_invoker;
private:
};

/* area recode class */
class t_area
{
public:
    t_area();

    t_area(const t_area& _origin);

    t_area(t_layer&                       _invoker     ,
           const std::vector<std::string> _contents_str);

    t_area& operator= (const t_area& _rhs);
};

/* point recode class */
class t_point
{
public:
    t_point();

    t_point(const t_area& _origin);

    t_point(t_layer&                       _invoker     ,
            const std::vector<std::string> _contents_str);

    t_point& operator=(const t_area& _rhs);
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