using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    class t_y_graph
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// </summary>
        public t_y_graph()
        {
            m_location  = new List< t_xy<int> >();
            m_adjacency = new List< List<uint> >();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="_origin"></param>
        public t_y_graph(t_graph _origin) : this()
        {
            
        }

        public List< t_xy<int> >  m_location;
        public List< List<uint> > m_adjacency;
    }
}
