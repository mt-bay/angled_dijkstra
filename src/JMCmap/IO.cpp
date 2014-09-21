#include <fstream>
#include <list>
#include <iomanip>

#include "IO.hpp"

#include "../coordinate/graph.hpp"
#include "../tools/tools.hpp"
namespace jmc
{

cd::t_graph t_jmc::jmc_to_graph(std::string _jmc_data_dir)
{
    std::list<std::string> file_list = mt::get_file_path_list
                                           (_jmc_data_dir, "*.dat");

    std::ifstream jmc;
    std::string line;

    for(std::list<std::string>::iterator it = file_list.begin();
        it != file_list.end()                                  ;
        it++                                                   )
    {
        jmc = std::ifstream(*it);
        while(std::getline(jmc, line))
        {

        }
    }
    

}

}