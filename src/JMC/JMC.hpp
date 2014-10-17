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
private:
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
private:

    /* method */
public :
    /* 
     * add road path
     * parameter    : path
     * return value : void
     * exception    : none
     */
    void add_road_path(const std::list< cd::t_xy<int> > _road);

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


    /* member variable and instance */
public:
    int m_mesh_number;
    std::vector< t_layer* > m_layer;
};

/* layer recode class */
class t_layer
{
    /* member variable and instance */
public:
    std::vector< t_line* > m_line;
};

/* line recode class */
class t_line
{
    /* member variable and instance */
public:
    std::vector< cd::t_xy<int>* > m_coordinate;
};

/* function */
volatile int location_to_primary_mesh(const cd::t_xy<int>   _source);
volatile int location_to_secondary_mesh(const cd::t_xy<int> _source);
}