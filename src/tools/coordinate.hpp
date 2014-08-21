#ifndef SRC_TOOLS_COORDINATE_H_
#define SRC_TOOLS_COORDINATE_H_


#include <iostream>
#include <string>
#include <type_traits>
#include <exception>


namespace cd
{
template <typename T>
class xy_t
{
    /* member variable */
public:
    T x, y;

    /* constracter, destracter */
public:
    /* 
     * default constractor
     * parameter : void
     * build     : origin point
     * exception : bad_typeid
     */
    xy_t()           throw(std::bad_typeid)
    {
        if (!std::is_arithmetic<T>::value)
            throw;
        x = static_cast<T>(0); y = static_cast<T>(0);
    }

    /* 
     * copy constractor
     * parameter : origin
     * build     : copy
     * exception : bad_typeid
     */
    xy_t(const xy_t<T>& _origin) throw(std::bad_typeid)
    {
        if (!std::is_arithmetic<T>::value)
            throw;
        x = _origin.x; y = _origin.y;
    }

    /* 
     * setter constractor
     * parameter : x, y
     * build     : point by parameter
     * exception : bad_typeid
     */
    xy_t(const T _x, const T _y) throw(std::bad_typeid)
    {
        if (!std::is_arithmetic<T>::value)
            throw;

        x = _x; y = _y;
    }

    ~xy_t()
    {

    }

    /* method */
public:
    std::string toString() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

private:
};

}

#endif //SRC_TOOLS_COORDINATE_H_