#include <list>
#include <iomanip>

#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"
#include "../dijkstra/dijkstra.hpp"
#include "../coordinate/graph.hpp"

#include "../log/log.hpp"

#include "../tools/define.hpp"

namespace jmc
{

t_JMC::t_JMC()
{
    

}


t_JMC::t_JMC(const di::t_dijkstra& _dijkstra) : t_JMC::t_JMC()
{
#ifdef _DEBUG
    io::t_log::get_instance().write_line("dijkstra result to JMC file(s)");
#endif // _DEBUG

    std::vector<unsigned int>::iterator it_path;
    std::list< cd::t_xy<int> > buf_path;

    for(int i = 0; i < _dijkstra.m_path->size(); ++i)
    {
        buf_path.clear();
        for(it_path =  _dijkstra.m_path->at(i).begin();
            it_path != _dijkstra.m_path->at(i).end();
            ++it_path                                  )
        {
            buf_path
                .push_back(*_dijkstra.m_graph->m_node_location->at(*it_path));
        }
        add_path(buf_path);
    }


}


t_JMC::~t_JMC()
{
}


void t_JMC::add_path(const std::list<cd::t_xy<int> >& _path)
{
    int buf_primary_mesh;
    int buf_secondary_mesh;

    std::list< cd::t_xy<int> >::const_iterator it_path;
    for(it_path =  _path.begin();
        it_path != _path.end();
        ++it_path)
    {
        buf_primary_mesh = location_to_primary_mesh(*it_path);
        buf_secondary_mesh = location_to_secondary_mesh(*it_path);
    }
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