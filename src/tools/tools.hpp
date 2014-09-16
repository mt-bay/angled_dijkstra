#ifndef SRC_TOOLS_TOOLS_H
#define SRC_TOOLS_TOOLS_H



#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace mt
{
/* function */
/* 
 * std::list to std::vector
 * parameter    : std::list
 * return value : std::vector
 * exception    : none
 */
template<typename T>
std::vector<T> list_to_vector(const std::list<T>& _source);

/* 
 * split string
 * parameter    : source string, delimiter
 * return value : splited string list
 + exception    : none
 */
std::list<std::string> split_l  (const std::string _source,
                                 const std::string _delim );

/* 
 * split string
 * parameter    : source string, delimiter
 * return value : splited string vector
 + exception    : none
 */
std::vector<std::string> split_v(const std::string _source,
                                 const std::string _delim );

/* 
 * std::vector to std::list
 * parameter    : std::vector
 * return value : std::list
 * exception    : none
 */
template<typename T>
std::list<T> vector_to_list(const std::vector<T>& _source);

}
//#include "tools.cpp"

#endif //!SRC_TOOLS_TOOLS_H