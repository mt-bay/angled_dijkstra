using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    /// <summary>
    /// 2-dimentional decalt point class
    /// </summary>
    /// <typeparam name="T">point type</typeparam>
    class t_xy<T>
        where T : struct
    {
        
        /* constructor */
        public t_xy()
        {
            x = default(T);
            y = default(T);
        }
        public t_xy(t_xy<T> _origin)
        {
            x = _origin.x;
            y = _origin.y;
        }
        public t_xy(T _x, T _y)
        {
            x = _x;
            y = _y;
        }
        /* destructor */
        ~t_xy()
        {

        }

        /* operator overload */
        public static t_xy<T> operator + (t_xy<T> _lhs, t_xy<T> _rhs)
        {
            return new t_xy<T>((dynamic)_lhs.x + (dynamic)_rhs.x, 
                               (dynamic)_lhs.y + (dynamic)_rhs.y);
        }
        
        public static t_xy<T> operator - (t_xy<T> _lhs, t_xy<T> _rhs)
        {
            return new t_xy<T>((dynamic)_lhs.x - (dynamic)_rhs.x,
                               (dynamic)_lhs.x - (dynamic)_rhs.y);
        }

        public static t_xy<T> operator * (t_xy<T> _lhs, double _rhs)
        {
            return new t_xy<T>((dynamic)_lhs.x * _rhs,
                               (dynamic)_lhs.y * _rhs);
        }

        public static bool    operator ==(t_xy<T> _lhs, t_xy<T> _rhs)
        {
            return (((dynamic)_lhs.x == (dynamic)_rhs.x) &&
                    ((dynamic)_lhs.y == (dynamic)_rhs.y));
        }

        public static bool    operator !=(t_xy<T> _lhs, t_xy<T> _rhs)
        {
            return !(_lhs == _rhs);
        }


        /* override method */
        public override string ToString()
        {
            return "(" + x.ToString() + ", " + y.ToString() + ")";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
            {
                return false;
            }

            t_xy<T> target = (t_xy<T>)obj;
            
            return ((dynamic)this.x == (dynamic)target.x &&
                    (dynamic)this.y == (dynamic)target.y);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /* static method */


        /* method */
        

        /* const value */


        /* static value and instance */


        /* member value and instance */
        public T x, y;


    }
}
