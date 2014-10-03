﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    class t_graph
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// </summary>
        public t_graph()
        {
            set_graph_size(0);
        }

        /// <summary>
        /// size setter constructor
        /// </summary>
        /// <param name="_size">size of graph</param>
        public t_graph(int _size)
        {
            set_graph_size(0);
        }


        /* destructor */
        ~t_graph()
        {

        }


        /* operator overload */


        /* static method */
        

        /* method */
        /// <summary>
        /// add location data
        /// </summary>
        /// <param name="_data">adding data</param>
        /// <param name="_prev_is_adjacency">prev node is adjacency</param>
        public void add_location(t_xy<long> _data,
                                 bool       _prev_is_adjacency = false)
        {
            m_adjacency_matrix.Add(new List<bool>(m_location.Count));
            for(int i = 0; i < m_adjacency_matrix.Count; ++i)
            {
                m_adjacency_matrix[i].Add(false);
            }

            m_location.Add(new t_xy<long>(_data));

            if (m_location.Count >= 2)
            {
                set_adjacency(m_location.Count - 1,
                              m_location.Count - 2,
                              _prev_is_adjacency);

                set_adjacency(m_location.Count - 2,
                              m_location.Count - 1,
                              _prev_is_adjacency);
            }

            return;
        }

        public void add_stickey_location(t_xy<long> _data,
                                         bool       _prev_is_adjancecy = false)
        {
            for (int i = 0; i < m_location.Count; ++i)
            {
                if (m_location[i] == _data)
                {
                    set_adjacency(i                   ,
                                  m_location.Count - 1,
                                  _prev_is_adjancecy  );

                    set_adjacency(m_location.Count - 1,
                                  i                   ,
                                  _prev_is_adjancecy  );

                    return;
                }
            }

            add_location(_data, _prev_is_adjancecy);
            return;
        }

        /// <summary>
        /// set adjacency data
        /// </summary>
        /// <param name="_src_node_number">src. node number</param>
        /// <param name="_dst_node_number">dst. node number</param>
        /// <param name="_is_adjacency">src. to dst. is adjacency</param>
        public void set_adjacency(int  _src_node_number,
                                  int  _dst_node_number,
                                  bool _is_adjacency   )
        {
            if(_src_node_number <  0 ||
               _src_node_number >= m_adjacency_matrix.Count)
            {
                throw new IndexOutOfRangeException
                            ("invalid src. node number");
            }
            if(_dst_node_number <  0 ||
               _dst_node_number >= m_adjacency_matrix.Count)
            {
                throw new IndexOutOfRangeException
                            ("invalid dst. node number");
            }

            m_adjacency_matrix[_src_node_number][_dst_node_number]
                = _is_adjacency;

            return;

        }

        /// <summary>
        /// set location data
        /// </summary>
        /// <param name="_index">index</param>
        /// <param name="_data">set data</param>
        public void set_location(int _index, t_xy<long> _data)
        {
            if(_index < 0)
            {
                throw new IndexOutOfRangeException("invalid index");
            }

            if(_index >= m_location.Count)
            {
                add_graph_size(_index - (m_location.Count - 1));
            }

            m_location[_index] = new t_xy<long>(_data);

            return;
        }

        /// <summary>
        /// add size of graph
        /// </summary>
        /// <param name="_size">add size</param>
        private void add_graph_size(int _size)
        {
            if(_size < 0)
            {
                return;
            }

            for(int i = 0; i < _size; ++i)
            {
                m_adjacency_matrix.Add(new List<bool>(m_location.Count));
                for(int j = 0; j < m_adjacency_matrix.Count; ++j)
                {
                    m_adjacency_matrix[i].Add(false);
                }

                m_location.Add(new t_xy<long>());
            }

            return;
        }

        /// <summary>
        /// set size of graph
        /// </summary>
        /// <param name="_size">size of graph</param>
        private void set_graph_size(int _size)
        {
            if(_size < 0)
                return;

            m_location = new List<t_xy<long> >((int)_size);
            m_adjacency_matrix = new List< List<bool> >((int)_size);

            add_graph_size(_size);

            return;
        }


        /* member value and instance */
        public List< t_xy<long> > m_location;
        public List< List<bool> > m_adjacency_matrix;

    }
}
