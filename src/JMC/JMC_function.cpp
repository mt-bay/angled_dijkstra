#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

#include "../tools/define.hpp"

namespace jmc
{
volatile
int location_to_primary_mesh(const cd::t_xy<int> _source)
{
    return ((_source.y / MESH_LOCATION_MAX_Y) / SECONDARY_MESH_MAX)
            * 100
         + ((_source.x / MESH_LOCATION_MAX_X) / SECONDARY_MESH_MAX)
            * 1;
}
volatile
int location_to_secondary_mesh(const cd::t_xy<int> _source)
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