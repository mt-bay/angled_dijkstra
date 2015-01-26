#include <direct.h>
#include <sys/stat.h>

#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iomanip>
#include <Windows.h>

#include "tools.hpp"


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


template<typename K, typename T>
std::list<K> get_keys(const std::map<K, T>& _source)
{
    std::list<K>   result;
    std::map<K, V>::const_iterator it;

    for(it = _source.begin(); it != _source.end(); ++it)
    {
        result.push_back(it->first);
    }

    return result;
}


void mkdir(const std::string& _file_path)
{
    std::string path_last = _file_path;
    int found             = 0;
    std::string dir       = "";

    int buf_int           = 0;
    struct stat buf_stat;

    while((found = path_last.find_first_of("\\")) != std::string::npos)
    {
        dir       += ((dir == "")? "" : "\\") + path_last.substr(0, found);
        path_last  = (found + 1 < (int)path_last.size())?
                        path_last.substr(found + 1) : "";

        buf_int   = stat(dir.c_str(), &buf_stat);
        if(buf_int != 0)
        {
            _mkdir(dir.c_str());
        }
    }

    return;
}


std::string file_path_to_file_name(const std::string _file_path)
{
    size_t found = _file_path.find_last_of("\\");
    if(found == std::string::npos)
    {
        return _file_path;
    }
    if(found + 1 == _file_path.size())
    {
        return "";
    }

    return _file_path.substr(found + 1);
}


std::string substr_byte(const std::string& _source,
                        const size_t       _begin ,
                        const size_t       _length)
{
    std::string result;
    for(size_t s = 0; s < _length; ++s)
    {
        result += _source.c_str()[_begin + s];
    }
    return result;
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