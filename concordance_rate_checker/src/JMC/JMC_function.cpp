#include <vector>

#include "JMC.hpp"

#include "../coordinate/coordinate.hpp"

#include "../tools/define.hpp"

#include "../log/log.hpp"

namespace jmc
{
std::vector<int> location_to_primary_mesh(const cd::t_xy<int> _source)
{
    std::vector<int> result = std::vector<int>();
    result.push_back(((_source.y / MESH_LOCATION_MAX_Y)
                        / (SECONDARY_MESH_MAX + 1)) * 100
                   + ((_source.x / MESH_LOCATION_MAX_X)
                        / (SECONDARY_MESH_MAX + 1)) *   1);

    int buf_int = result[0];

    if(_source.y % (MESH_LOCATION_MAX_Y * (SECONDARY_MESH_MAX + 1)) == 0)
    {
        buf_int -= 100;
    }
    if(_source.x % (MESH_LOCATION_MAX_X * (SECONDARY_MESH_MAX + 1)) == 0)
    {
        buf_int -= 1;
    }

    if(result.at(0) == buf_int)
    {
        return result;
    }

    result.push_back(buf_int);
    return result;
}


std::vector<int> location_to_secondary_mesh(const cd::t_xy<int> _source)
{
    std::vector<int> result = std::vector<int>();
    result.push_back(((_source.y / MESH_LOCATION_MAX_Y)
                        / (SECONDARY_MESH_MAX + 1)) * 10000
                   + ((_source.x / MESH_LOCATION_MAX_X)
                        / (SECONDARY_MESH_MAX + 1)) *   100
                   + ((_source.y / MESH_LOCATION_MAX_Y)
                        % (SECONDARY_MESH_MAX + 1)) *    10
                   + ((_source.x  / MESH_LOCATION_MAX_X)
                        % (SECONDARY_MESH_MAX + 1)) *     1);

    int buf_int = result[0];

    if(_source.y % (MESH_LOCATION_MAX_Y) == 0)
    {
        if(_source.y % (MESH_LOCATION_MAX_Y * (SECONDARY_MESH_MAX + 1)) == 0)
        {
            buf_int -= 10000;
            buf_int += SECONDARY_MESH_MAX * 10;
        }
        else
        {
            buf_int -= 10;
        }
    }

    if(_source.x % (MESH_LOCATION_MAX_X) == 0)
    {
        if(_source.x % (MESH_LOCATION_MAX_X * (SECONDARY_MESH_MAX + 1)) == 0)
        {
            buf_int -= 100;
            buf_int += SECONDARY_MESH_MAX *  1;
        }
        else
        {
            buf_int -= 1;
        }
    }

    if(result.at(0) == buf_int)
    {
        return result;
    }

    result.push_back(buf_int);
    return result;
}


cd::t_xy<int> encode_coordinate(const cd::t_xy<int> _source        ,
                                const int           _secondary_mesh)
{

    cd::t_xy<int> mesh_padding = cd::t_xy<int>
                                    (((((_secondary_mesh /   100) % 100)
                                        * (SECONDARY_MESH_MAX + 1))
                                        + (_secondary_mesh /   1) %  10)
                                        * MESH_LOCATION_MAX_X,
                                     ((((_secondary_mesh / 10000) % 100)
                                        * (SECONDARY_MESH_MAX + 1))
                                        + (_secondary_mesh /  10) %  10)
                                        * MESH_LOCATION_MAX_Y);

    return cd::t_xy<int>(_source.x % mesh_padding.x,
                         _source.y % mesh_padding.y);
}


}