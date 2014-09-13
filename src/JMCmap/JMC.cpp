#include <iostream>
#include <string>


namespace cd
{
class t_graph;
}

namespace jc
{

class t_jmc
{
    /* member valiable */

    /*  */

    /* method */
public:
    /* 
     * jmc data files to graph
     * parameter    : jmc data file directory
     * return value : generated graph
     * exception    : 
     */
    static cd::t_graph jmc_to_graph();
};

}