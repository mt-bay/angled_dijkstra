#include <vector>
#include <map>

#include "../coordinate/coordinate.hpp"


namespace jmc
{

/* class to output JMC file(s) */
class t_JMC
{
    /* constructor */
public :
private:

    /* destructor */

    /* static method */
public :
    void import_dijkstra();
private:

    /* method */
public :
private:
    int location_to_primary_mesh();
    int location_to_secondary_mesh();


    /* member variable and instance */
public :
    std::map<int, std::vector<std::string> > jmc_content;

    std::map<int, std::map<int, unsigned int> > mesh_recode_index;
    std::map<int, std::map<int, unsigned int> > line_recode_index;

    unsigned int  buf_index;
    cd::t_xy<int> buf_location;
    int           buf_primary_mesh;
    int           buf_secondary_mesh;

    bool          found_secondary_mesh;

private:

};

}