#include "tools.hpp"


namespace mt
{
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