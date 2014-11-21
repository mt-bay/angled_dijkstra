using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    class t_pc_graph
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// </summary>
        public t_pc_graph()
        {
            m_location  = new List< t_xy<int> >();
            m_adjacency = new List< List<int> >();
            m_link_cost = new List< List<double> >();
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="_origin"></param>
        public t_pc_graph(t_pc_graph _origin) : this()
        {
            for(int i = 0; i < _origin.m_location.Count; ++i)
            {
                m_location[i] = new t_xy<int>(_origin.m_location[i]);
            }
            for(int i = 0; i < _origin.m_adjacency.Count; ++i)
            {
                m_adjacency[i] = new List<int>();
                for(int j = 0; j < _origin.m_adjacency[i].Count; ++j)
                {
                    m_adjacency[i][j] = _origin.m_adjacency[i][j];
                }
            }
            for(int i = 0; i < _origin.m_link_cost.Count; ++i)
            {
                m_link_cost[i] = new List<double>();
                for(int j = 0; j < _origin.m_link_cost[i].Count; ++j)
                {
                    m_link_cost[i][j] = _origin.m_link_cost[i][j];
                }
            }

        }


        /// <summary>
        /// add adjacency
        /// </summary>
        /// <param name="_src">src. node number</param>
        /// <param name="_dst">dst. node number</param>
        public void add_adjacency(int    _src                ,
                                  int    _dst                ,
                                  bool   _is_adjacency = true, 
                                  double _link_cost    = 0.0d)
        {
            if(!_is_adjacency)
            {
                return;
            }
            if(_src == _dst)
            {
                return;
            }

            bool add_src_to_dst = true;
            for(int i = 0; i < m_adjacency[_src].Count; ++i)
            {
                if(m_adjacency[_src][i] == _dst)
                {
                    add_src_to_dst = false;
                }
            }
            if(add_src_to_dst)
            {
                m_adjacency[_src].Add(_dst);
                m_link_cost[_src].Add(_link_cost);
            }
            
            bool add_dst_to_src = true;
            for(int i = 0; i < m_adjacency[_dst].Count; ++i)
            {
                if(m_adjacency[_dst][i] == _src)
                {
                    add_dst_to_src = false;
                }
            }
            if(add_dst_to_src)
            {
                m_adjacency[_dst].Add(_src);
                m_link_cost[_dst].Add(_link_cost);
            }

        }


        /// <summary>
        /// add location data
        /// </summary>
        /// <param name="_target">adding location</param>
        /// <returns>added node number</returns>
        public int add_location(t_xy<int> _source              ,
                                bool      _is_adjacency = false,
                                int       _prev         = -1   ,
                                double    _link_cost    = 0.0d )
        {
            int prev = (_prev < 0)? m_location.Count - 1 : _prev;
            m_location.Add(new t_xy<int>(_source));
            m_adjacency.Add(new List<int>());

            add_adjacency(prev, m_location.Count - 1, _is_adjacency);

            return m_location.Count - 1;
        }


        /// <summary>
        /// add location data
        /// stick adjancecy data if adding data is not unique
        /// </summary>
        /// <param name="_source">adding data</param>
        /// <param name="_is_adjacency">prev node number is adjacency</param>
        /// <param name="_prev">prev node number</param>
        /// <returns></returns>
        public int add_stickey_location(t_xy<int> _source              ,
                                        bool      _is_adjacency = false,
                                        int       _prev = -1           )
        {
            int prev = (_prev < 0)? m_location.Count - 1 : _prev;
            for(int i = 0; i < m_location.Count; ++i)
            {
                if(_source == m_location[i])
                {
                    add_adjacency(_prev, i, _is_adjacency);

                    return i;
                }
            }

            return add_location(_source, _is_adjacency, _prev);
        }

        /// <summary>
        /// this instance to csv
        /// </summary>
        /// <param name="_file_path">file path</param>
        public void to_csv(string _file_path)
        {
            util.mkdir(_file_path);

            StreamWriter csv = new StreamWriter(_file_path);

            for(int i = 0; i < m_location.Count; ++i)
            {
                csv.Write(m_location[i].x.ToString() + ",");
                csv.Write(m_location[i].y.ToString());
                for(int j = 0; j < m_adjacency[i].Count; ++j)
                {
                    csv.Write(",");
                    csv.Write(m_adjacency[i][j].ToString());
                }
                if(i < m_location.Count - 1)
                {
                    csv.WriteLine();
                }
            }
            csv.Close();
        }


        

        public List< t_xy<int>    > m_location;
        public List< List<int>    > m_adjacency;
        public List< List<double> > m_link_cost;
    }
}
