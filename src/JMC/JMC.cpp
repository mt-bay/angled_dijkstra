#include <list>
#include <iomanip>

#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"
#include "../dijkstra/dijkstra.hpp"
#include "../coordinate/graph.hpp"

#include "../tools/define.hpp"

namespace jmc
{

t_JMC::t_JMC()
{
    buf_index            = 0;
    buf_location         = new cd::t_xy<int>();
    buf_primary_mesh     = 0;
    found_secondary_mesh = 0;

}

t_JMC::t_JMC(const di::t_dijkstra& _dijkstra) : t_JMC::t_JMC()
{
#ifdef _DEBUG
    io::t_log::get_instance().write_info("dijkstra result to JMC file(s)");
#endif // _DEBUG

    //body of process
    for(unsigned int i = 0; i < _dijkstra.m_path->size(); ++i)
    {
        for(unsigned int j = 0; j < _dijkstra.m_path->at(i).size(); ++j)
        {
            buf_index          = _dijkstra.m_path->at(i).at(j);
            buf_location       = _dijkstra.m_graph->m_node_location->at(buf_index);
            buf_primary_mesh   = location_to_primary_mesh(*buf_location);
            buf_secondary_mesh = location_to_secondary_mesh(*buf_location);

            if(jmc_content.count(buf_primary_mesh) == 0)
            {
                jmc_content[buf_primary_mesh] = std::vector<std::string>();
            }

            if(mesh_recode_index.count(buf_secondary_mesh) == 0)
            {
                found_secondary_mesh = false;
                for(unsigned int k = 0;
                    k < mesh_recode_index.at(buf_primary_mesh).size();
                    ++k)
                {
                    if(buf_secondary_mesh 
                     < mesh_recode_index[buf_primary_mesh][k])
                    {

                    }
                }
            }
        }
    }
}

t_JMC::~t_JMC()
{
    delete buf_location;
}


void t_JMC::make_jmc_content(const int _primary_mesh_number)
{
    if(jmc_content.count(_primary_mesh_number) != 0)
    {
        return;
    }

    jmc_content[_primary_mesh_number]       = std::vector<std::string>();
    mesh_recode_index[_primary_mesh_number] = std::map<int, unsigned int>();
    line_recode_index[_primary_mesh_number] = std::map<int, unsigned int>();
}


void t_JMC::add_mesh_header
    (const unsigned int _line_number, const int _secondary_mesh_number)
{
    int primary_mesh_number = _secondary_mesh_number / 100;
    if(jmc_content.count(primary_mesh_number) == 0)
    {
        make_jmc_content(primary_mesh_number);
    }

    std::map<int, unsigned int>::iterator it;
    for(it = mesh_recode_index[primary_mesh_number].begin();
        it != mesh_recode_index[primary_mesh_number].end();
        ++it)
    {
        
    }
}

void t_JMC::add_line
    (const unsigned int _line_number, const std::string& _content)
{

}

volatile
int t_JMC::location_to_primary_mesh(const cd::t_xy<int> _source) const
{
    return ((_source.y / MESH_LOCATION_MAX_Y) / SECONDARY_MESH_MAX)
            * 100
         + ((_source.x / MESH_LOCATION_MAX_X) / SECONDARY_MESH_MAX)
            * 1;
}
volatile
int t_JMC::location_to_secondary_mesh(const cd::t_xy<int> _source) const
{
    return ((_source.y / MESH_LOCATION_MAX_Y) / SECONDARY_MESH_MAX)
            * 10000
         + ((_source.x / MESH_LOCATION_MAX_X) / SECONDARY_MESH_MAX)
            * 100
         + ((_source.y / MESH_LOCATION_MAX_Y) % SECONDARY_MESH_MAX)
            * 10
        + ((_source.x / MESH_LOCATION_MAX_X) % SECONDARY_MESH_MAX)
            * 1;
}


}