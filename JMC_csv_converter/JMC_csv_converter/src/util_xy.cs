using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    class util_xy
    {

        /// <summary>
        /// get line length that made to p0 and p1
        /// </summary>
        /// <param name="_p0">line source node</param>
        /// <param name="_p1">line destination node</param>
        /// <returns></returns>
        public static double length<T1, T2>(t_xy<T1> _p0, t_xy<T2> _p1)
            where T1 : struct
            where T2 : struct
            
        {
            return
                Math.Sqrt(Math.Pow((dynamic)_p1.x - (dynamic)_p0.x, 2.0d)
                        + Math.Pow((dynamic)_p1.y - (dynamic)_p0.y, 2.0d));
        }
    }
}
