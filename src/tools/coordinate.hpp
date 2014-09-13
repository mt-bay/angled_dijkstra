#ifndef SRC_TOOLS_COORDINATE_H_
#define SRC_TOOLS_COORDINATE_H_

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif  //_USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <type_traits>
#include <exception>

#include <math.h>
#include <cmath>

namespace cd
{

/* class */
/* 
 * Two-dimensional coordinates class
 */
template <typename T>
class t_xy
{
    /* member variable and instance */
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
    t_xy<T>()           throw(std::bad_typeid)
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
    t_xy<T>(const t_xy<T>& _origin) throw(std::bad_typeid)
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
    t_xy<T>(const T _x, const T _y) throw(std::bad_typeid)
    {
        if (!std::is_arithmetic<T>::value)
            throw;

        x = _x; y = _y;
    }

    ~t_xy()
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
    t_xy<T>& operator= (const t_xy<T>& _rhs)
    {
        this->x = static_cast<T>(_rhs.x);
        this->y = static_cast<T>(_rhs.y);
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
        return t_xy<T>(this->x + static_cast<T>(_rhs.x),
                       this->y + static_cast<T>(_rhs.y));
    }

    /* 
     * division operator
     * parameter    : right hand side
     * return value : {A.x - B.x, A.y - B.y}(in case A-B)
     * exception    : none
     */
    t_xy<T> operator- (const t_xy<T>& _rhs) const
    {
        return t_xy<T>(this->x - static_cast<T>(_rhs.x),
                       this->y - static_cast<T>(_rhs.y));
    }

    /* 
     * addition assignment operator
     * parameter    : right hand side
     * return value : assignmented instance reference
     * exception    : none
     */
    t_xy<T>& operator+=(const t_xy<T>& _rhs)
    {
        this->x += static_cast<T>(_rhs.x);
        this->y += static_cast<T>(_rhs.y);
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
    template<typename T1, typename T2>
    static long double length(const t_xy<T1> _src, const t_xy<T2> _dst)
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
     * t_xy<T1> to t_xy<T>
     * parameter    : t_xy<T1>
     * return value : t_xy<T>
     * exception    : none
     */
    template<typename T1>
    static t_xy<T> cast(const t_xy<T1> _origin)
    {
        return t_xy<T>(static_cast<T>(_origin.x), static_cast<T>(_origin.y));
    }

    /* 
     * counterclockwise rotation
     * parameter    : source, rotation angle, origin point
     * return value : rotationed source point
     * exception    : none
     */
    template<typename T1>
    static t_xy<T> rotation(const t_xy<T> _source, const double theta,
                            const t_xy<T1> _origin)
    {
        t_xy<T> origin  = t_xy<T>::cast(_origin);
        t_xy<T> src_rel = _source - origin;
        return t_xy<T>
               ((src_rel.x * cos(theta) - src_rel.y * sin(theta)) + origin.x,
                (src_rel.x * sin(theta) + src_rel.y * cos(theta)) + origin.y);
    }

    /* 
     * get angle of source to destination via via
     * parameter    : source, via, destination
     * return value : anele
     * exception    : none
     */
    template<typename T1, typename T2, typename T3>
    static double get_angle(const t_xy<T1> _src,
                            const t_xy<T2> _via,
                            const t_xy<T3> _dst)
    {
        t_xy<double> src = t_xy<double>((double)_src.x,
                                        (double)_src.y);

        t_xy<double> via = t_xy<double>((double)_via.x - (double)src.x,
                                        (double)_via.y - (double)src.y);

        t_xy<double> dst = t_xy<double>((double)_dst.x - (double)src.x,
                                        (double)_dst.y - (double)src.y);

        double ang_via = std::atan2(via.y, via.x);
        if(ang_via < 0.0)
            ang_via = M_PI + (-ang_via);
        via = t_xy<double>::rotation(via, -ang_via, src);
        dst = t_xy<double>::rotation(dst, -ang_via, src);

        dst -= via;
        double ang_dst = std::atan2(dst.y, dst.x);
        if(ang_dst < 0.0)
            ang_dst = M_PI + (-ang_dst);
        
        return ang_dst;
    }




private:

};

}

#endif //SRC_TOOLS_COORDINATE_H_