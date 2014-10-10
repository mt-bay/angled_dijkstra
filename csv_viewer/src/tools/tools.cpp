#include "tools.hpp"

#include <cstdlib>
#include <exception>
#include <Windows.h>

namespace mt
{
std::list<std::string> get_file_path_list(const std::string _directory, 
                                          const std::string _filter   )
{
    const size_t full_path_cap = 256;
    char* full_path_c = new char[full_path_cap];
    _fullpath(full_path_c       ,
              _directory.c_str(),
              full_path_cap     );

    std::string full_path = full_path_c;
    delete full_path_c;

    std::list<std::string> result;

    WIN32_FIND_DATAA fd;

    std::string fil = full_path + _filter;

    HANDLE found = FindFirstFileA(fil.c_str(), &fd);

    if(found == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    do
    {
        if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            result.push_back(fd.cFileName);
        }
    }
    while(FindNextFileA(found, &fd));

    FindClose(found);

    return result;
}


template<typename T>
std::vector<T> list_to_vector(const std::list<T>& _source)
{
    std::vector<T> result = std::vector<T>();

    for(std::list<T>::iterator it = _source.begin();
        it != _source.end();
        ++it)
    {
        result.push_back(*it);
    }

    return result;
}


std::string file_path_to_file_name(const std::string _file_path)
{
    return "";
}

std::list<std::string> split_l(const std::string _source,
                               const std::string _delim )
{
    std::list<std::string> result;
    size_t index = 0, found;
    while((found = _source.find(_delim, index)) != std::string::npos)
    {
        result.push_back(std::string(_source, index, found - index));
        index = found + _delim.size();
    }
    result.push_back(std::string(_source, index, _source.size() - index));

    return result;
}


std::vector<std::string> split_v(const std::string _source,
                                 const std::string _delim )
{
    std::vector<std::string> result;
    size_t index = 0, found;
    while((found = _source.find(_delim, index)) != std::string::npos)
    {
        result.push_back(std::string(_source, index, found - index));
        index = found + _delim.size();
    }
    result.push_back(std::string(_source, index, _source.size() - index));

    return result;
}


template<typename T>
std::list<T> vector_to_list(const std::vector<T>& _source)
{
    std::list<T> result = std::vector<T>();

    for(std::vector<T>::iterator it = _source.begin();
        it != _source.end();
        ++it)
    {
        result.push_back(*it);
    }

    return result;
}

}