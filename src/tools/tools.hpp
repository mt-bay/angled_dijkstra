#pragma once


#include <string>
#include <vector>
#include <list>
#include <map>


namespace mt
{
/* function */
/* 
 * get file list in directory
 * parameter    : search directory
 * return value : file list
 * exception    : none
 */
std::list<std::string> get_file_path_list(const std::string _directory     ,
                                          const std::string _filter = "*.*");

/* 
 * get map key(s)
 * parameter    : map
 * return value : map's key(s)
 * exception    : none
 */
template<typename K, typename T>
std::list<K> get_keys<K, T>(const std::map<K, T>& _source);

/* 
 * std::list to std::vector
 * parameter    : std::list
 * return value : std::vector
 * exception    : none
 */
template<typename T>
std::vector<T> list_to_vector(const std::list<T>& _source);

/* 
 * file path to file name
 * ex : "./path/file_name.txt" -> "file_name"
 * parameter    : file path
 * return value : file name or ""(if file is not found)
 * exception    : none
 */
std::string file_path_to_file_name(const std::string _file_path);

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