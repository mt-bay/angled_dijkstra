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
class t_xy
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
     * exception : std::bad_typeid
     */
    t_xy()           throw(std::bad_typeid)
    {
        if (!std::is_arithmetic<T>::value)
            throw;
        x = static_cast<T>(0); y = static_cast<T>(0);
    }

    /* 
     * copy constractor
     * parameter : origin
     * build     : deep copy
     * exception : std::bad_typeid
     */
    t_xy(const xy_t<T>& _origin) throw(std::bad_typeid)
    {
        if (!std::is_arithmetic<T>::value)
            throw;
        x = _origin.x; y = _origin.y;
    }

    /* 
     * setter constractor
     * parameter : x, y
     * build     : point by parameter
     * exception : std::bad_typeid
     */
    t_xy(const T _x, const T _y) throw(std::bad_typeid)
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
    /* 
     * assignment operator
     * assign rhs instance to this instance
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_xy<T>& operator= (const xy_t<T>& _rhs)
    {
        x = _rhs.x;
        y = _rhs.y;
        return *this;
    }

    /* 
     * addition operator
     * parameter    : right hand side
     * return value : {A.x + B.x, A.y + B.y}(in case A+B)
     * exception    : none
     */
    t_xy<T>  operator+ (const t_xy<T>& _rhs) const
    {
        return t_xy<T>(this->x + _rhs.x,
                       this->y + _rhs.y);
    }

    /* 
     * division operator
     * parameter    : right hand side
     * return value : {A.x - B.x, A.y - B.y}(in case A-B)
     * exception    : none
     */
    t_xy<T> operator- (const t_xy<T>& _rhs) const
    {
        return t_xy<T>(this->x - _rhs.x,
                       this->y - _rhs.y);
    }

    /* 
     * addition assignment operator
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_xy<T>& operator+=(const t_xy<T>& _rhs)
    {
        x += _rhs.x;
        y += _rhs.y;
        return *this;
    }

    /* 
     * division assignment operator
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_xy<T>& operator-=(const t_xy<T>& _rhs)
    {
        x -= _rhs.x;
        y -= _rhs.y;
        return *this;
    }


    /* method */
public:
    /* 
     * length in p0 to p1
     * parameter    : source, destination
     * return value : length of p0 to p1
     * exception    : none
     */
    static long double length(const t_xy<T> _src, const t_xy<T> _dst) const
    {
    t_xy<long double> p0 = t_xy<long double>
                               ((long double)_src.x, (long double)_src.y);
    t_xy<long double> p1 = t_xy<long double>
                               ((long double)_dst.x, (long double)_dst.y);

    t_xy<long double> p = t_xy<long double>
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

    /* 
     * get angle of source to destination via via
     * parameter    : source, via, destination
     * return value : anele
     * exception    : none
     */
    static double get_angle(const t_xy<T> _src,
                            const t_xy<T> _via,
                            const t_xy<T> _dst) const
    {
        t_xy<T> src = t_xy<T>(_src.x, -_src.y);
        t_xy<T> via = t_xy<T>(_via.x - src.x, -_via.y - src.y);
        t_xy<T> dst = t_xy<T>(_dst.x - src.x, -_dst.y - src.y);




    }


private:

};

}

#endif //SRC_TOOLS_COORDINATE_H_