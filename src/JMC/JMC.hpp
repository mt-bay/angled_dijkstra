#pragma once


#include <vector>
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
    void make_jmc_content(const int _primary_mesh_number);

    void add_mesh_header
        (const unsigned int _line_number, const int _secondary_mesh_number);
    void add_coordinate
        (const unsigned int _line_recode_index, const cd::t_xy<int> _content);
    void add_line
        (const unsigned int _line_number, const std::string& _content);

    void correct_mesh_header();

    volatile int location_to_primary_mesh(const cd::t_xy<int>   _source) const;
    volatile int location_to_secondary_mesh(const cd::t_xy<int> _source) const;


    /* member variable and instance */
public :
    std::map<int, std::vector<std::string> > jmc_content;
    /// mesh_line = std::map[primary][secondary]
    std::map<int, std::map<int, unsigned int> >
        mesh_recode_index;
    /// index_line = std::map[primary][secondary][mesh_index]
    std::map<int, std::map<int, std::map<unsigned int, unsigned int> > >
        line_recode_index;
    /// num_of_coordinate = std::map[primary][secondary][mesh][line]
    std::map<int, 
        std::map<int, 
            std::map<unsigned int,
                std::map<unsigned int, unsigned int> > > > num_of_coordinate;

    unsigned int   buf_index;
    cd::t_xy<int>* buf_location;
    int            buf_primary_mesh;
    int            buf_secondary_mesh;

    bool           found_secondary_mesh;

private:

};

}