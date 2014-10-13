using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using JMC_csv_converter.src.JMC;


namespace JMC_csv_converter.src
{
    /// <summary>
    /// JMC io class
    /// </summary>
    class t_JMC
    {
        

        /* constructor */
        /// <summary>
        /// default constructor
        /// built empty t_JMC
        /// </summary>
        public t_JMC()
        {
            init();
        }

        /// <summary>
        /// jmc-data directory to graph
        /// </summary>
        /// <param name="_jmc_dir">jmc-data directory path</param>
        /// <returns>created graph</returns>
        public t_JMC(string _jmc_dir)
        {
            init();

            string jmc_dir_path = (Path.IsPathRooted(_jmc_dir))? 
                                    _jmc_dir :
                                    Path.GetFullPath(_jmc_dir);

            string[] jmc_files = Directory.GetFiles(_jmc_dir);

            int line_num;

            StreamReader file;
            string line;
            

            for(int i = 0; i < jmc_files.Length; ++i)
            {
                file = new StreamReader
                    (jmc_files[i]                     ,
                     Encoding.GetEncoding("Shift_JIS"));
                line_num = 0;

                t_logger.get_instance().write(@"read : " + jmc_files[i]);

                while(file.Peek() >= 0)
                {
                    ++line_num;

                    try
                    {
                        line = file.ReadLine();
                        analysis_line(line);
                    }
                    catch (FormatException e)
                    {
                        t_logger.get_instance().write_info
                            (@"catch in line " + line_num);
                        t_logger.get_instance().write_exception(e);
                    }
                }
            }
            t_logger.get_instance().write(@"read successful");
        }


        /* method */
        /// <summary>
        /// output coordinate list
        /// </summary>
        /// <param name="_output_file_path">output file path</param>
        public void out_coordinate_list(string _output_file_path)
        {
            t_logger.get_instance().write("output jmc coordinate list");

            StreamWriter out_file = new StreamWriter(_output_file_path);

            for (int i = 0; i < m_mesh.Count; ++i)
            {
                for (int j = 0;
                     j < m_mesh[i].m_layer.Count;
                     ++j)
                {
                    for (int k = 0;
                         k < m_mesh[i].m_layer[j].m_line.Count;
                         ++k)
                    {
                        for(int l = 0;
                            l < m_mesh[i].m_layer[j].m_line[k]
                               .m_coordinate.Count;
                            ++l)
                        {
                            out_file.WriteLine
                                ((m_mesh[i].m_padding
                                + m_mesh[i].m_layer[j].m_line[k]
                                 .m_coordinate[l]               ).ToString());
                        }
                    }
                }
            }
        }

        /// <summary>
        /// get number of coordinate
        /// </summary>
        /// <returns>number of coordinate</returns>
        public int get_coordinate_num()
        {
            int result = 0;
            for (int i = 0; i < m_mesh.Count; ++i)
            {
                for (int j = 0;
                     j < m_mesh[i].m_layer.Count;
                     ++j)
                {
                    for (int k = 0;
                         k < m_mesh[i].m_layer[j].m_line.Count;
                         ++k)
                    {
                        for(int l = 0;
                            l < m_mesh[i].m_layer[j].m_line[k]
                               .m_coordinate.Count;
                            ++l)
                        {
                            ++result;
                        }
                    }
                }
            }
            return result;
        }


        /// <summary>
        /// get upper-right of coordinate
        /// </summary>
        /// <returns></returns>
        public t_xy<int> get_coordinate_upper_right()
        {
            t_xy<int> result = new t_xy<int>(0, 0);
            t_xy<int> target = new t_xy<int>(0, 0);
            for (int i = 0; i < m_mesh.Count; ++i)
            {
                for (int j = 0;
                     j < m_mesh[i].m_layer.Count;
                     ++j)
                {
                    for (int k = 0;
                         k < m_mesh[i].m_layer[j].m_line.Count;
                         ++k)
                    {
                        for(int l = 0;
                            l < m_mesh[i].m_layer[j].m_line[k]
                               .m_coordinate.Count;
                            ++l)
                        {
                            target = m_mesh[i].m_padding
                                   + m_mesh[i].m_layer[j].m_line[k]
                                    .m_coordinate[l]               ;
                            if (result.x < target.x)
                            {
                                result.x = target.x;
                            }
                            if (result.y < target.y)
                            {
                                result.y = target.y;
                            }
                        }
                    }
                }
            }
            return result;
        }


        /// <summary>
        /// this instance to graph data
        /// </summary>
        /// <returns>generated graph</returns>
        public t_graph to_graph()
        {
            t_logger.get_instance().write_info("convert JMC to graph");

            t_graph result = new t_graph();

            int prev = 0;

            for (int i = 0; i < m_mesh.Count; ++i)
            {
                for (int j = 0;
                     j < m_mesh[i].m_layer.Count;
                     ++j)
                {
                    if (m_mesh[i].m_layer[j].m_code != 2)
                    {
                        continue;
                    }

                    for (int k = 0;
                         k < m_mesh[i].m_layer[j].m_line.Count;
                         ++k)
                    {
                        for(int l = 0;
                            l < m_mesh[i].m_layer[j].m_line[k]
                               .m_coordinate.Count;
                            ++l)
                        {
                            prev = result.add_stickey_location
                                (m_mesh[i].m_padding +
                                 m_mesh[i].m_layer[j].m_line[k]
                                .m_coordinate[l]               ,
                                 prev                          ,
                                 (l != 0));
                        }
                    }
                }
            }
            return result;
        }


        /// <summary>
        /// analysis line
        /// </summary>
        /// <param name="_line">string line</param>
        private void analysis_line(string _line)
        {
            //recode type check
            //    mesh recode
            if      (t_mesh.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.MESH;
                m_mesh.Add(t_mesh.line_to_mesh_header(_line));
                return;
            }

            t_mesh mesh = m_mesh[m_mesh.Count - 1];
            //    layer recode
            if (t_layer.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.LAYER;
                m_mesh[m_mesh.Count - 1].m_layer.Add
                    (t_layer.line_to_layer_header(_line));
                return;
            }
            t_layer layer = m_mesh[m_mesh.Count - 1]
                           .m_layer[m_mesh[m_mesh.Count - 1].m_layer.Count - 1];
            //    node recode
            if (t_node.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.NODE;
                return;
            }
            if (t_area.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.AREA;
                return;
            }
            //    line item recode
            if (t_line.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.LINE;
                layer.m_line.Add(t_line.line_to_line_item(_line));
                return;
            }
            //    point recode
            else if (t_point.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.POINT;
                return;
            }
            
            //coordinate recode or note recode
            switch (layer.m_code)
            {
                case 1 :
                    if (m_prev_analysis == e_analysis_type.LINE)
                    {
                        m_prev_analysis = e_analysis_type.COORDINATE;
                        layer.m_line[layer.m_line.Count - 1]
                            .add_coordinate_point_record(_line);
                    }
                    else if(m_prev_analysis == e_analysis_type.AREA)
                    {
                        m_prev_analysis = e_analysis_type.CONSTRUCT_LINE;
                    }

                    return;

                case 2 :
                    m_prev_analysis = e_analysis_type.COORDINATE;
                    layer.m_line[layer.m_line.Count - 1]
                        .add_coordinate_point_record(_line);

                    return;

                case 3 :
                    m_prev_analysis = e_analysis_type.COORDINATE;
                    layer.m_line[layer.m_line.Count - 1]
                        .add_coordinate_point_record(_line);

                    return;

                case 5 :
                    m_prev_analysis = e_analysis_type.COORDINATE;
                    layer.m_line[layer.m_line.Count - 1]
                        .add_coordinate_point_record(_line);

                    return;

                case 7 :
                    return;
            }
            
            throw new FormatException(@"unknown string : " + _line);
        }


        /// <summary>
        /// init instance
        /// </summary>
        private void init()
        {
            m_mesh  = new List<t_mesh>();
            m_prev_analysis = e_analysis_type.NONE;
        }

        /* member enum */
        private enum e_analysis_type
        {
            NONE          ,
            MESH          ,
            LAYER         ,
            NODE          ,
            AREA          ,
            LINE          ,
            POINT         ,
            COORDINATE    ,
            CONSTRUCT_LINE,
            NOTE          ,
        }


        /* static value and instance */
        public static Encoding ms_encode = Encoding.GetEncoding("shift_jis");

        /* member value and instance */
        //mesh
        private List<t_mesh>  m_mesh;

        //layer

        //line item

        //other
        private e_analysis_type m_prev_analysis;
    }
}
