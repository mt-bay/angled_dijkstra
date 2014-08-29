#ifndef SRC_TOOLS_COORDINATE_H_
#define SRC_TOOLS_COORDINATE_H_


#include <iostream>
#include <string>
#include <type_traits>
#include <exception>


namespace cd
{

/* class */
/* 
 * Two-dimensional coordinates class
 */
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
    
    /* operator overload */
public:
    xy_t<T>& operator= (const xy_t<T>& _rhs)
    {
        x = _rhs.x;
        y = _rhs.y;
        return *this;
    }

    /* method */
public:
    /* 
     * length in p0 to p1
     * parameter    : p0, p1
     * return value : length of p0 to p1
     * exception    : none
     */
    static long double length(xy_t<T> p0, xy_t<T> p1)
    {
    xy_t<long double> p0 = xy_t<long double>
                               ((long double)_p0.x, (long double)_p0.y);
    xy_t<long double> p1 = xy_t<long double>
                               ((long double)_p1.x, (long double)_p1.y);

    xy_t<long double> p = xy_t<long double>
                               (p1.x - p0.x, p1.y - p0.y);

    return sqrt(p.x * p.x + p.y * p.y);
    }

    /* 
     * this to string
     * parameter    : void
     * return value : this data of string
     * exception    : none
     */
    std::string toString() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

private:
};

}

#endif //SRC_TOOLS_COORDINATE_H_