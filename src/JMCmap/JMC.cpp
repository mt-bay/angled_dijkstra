#include <list>

#include "JMC.hpp"

#include "../coordinate/graph.hpp"
#include "../tools/tools.hpp"
namespace jmc
{

cd::t_graph t_jmc::jmc_to_graph(std::string _jmc_data_dir)
{
    std::list<std::string> file_list = mt::get_file_path_list
                                           (_jmc_data_dir, "*.dat");


}

}