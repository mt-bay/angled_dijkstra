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
            m_mesh  = new t_mesh();
            m_layer = new t_layer();
            m_prev_analysis = e_analysis_type.NONE;
        }

        /* method */
        /// <summary>
        /// jmc-data directory to graph
        /// </summary>
        /// <param name="_jmc_dir">jmc-data directory path</param>
        /// <returns>created graph</returns>
        public t_graph jmc_dat_directory_to_graph(string _jmc_dir)
        {
            t_xy<long> margin = new t_xy<long>(0, 0);
            t_graph    result = new t_graph();

            string jmc_dir_path = (Path.IsPathRooted(_jmc_dir))? 
                                    _jmc_dir :
                                    Path.GetFullPath(_jmc_dir);

            string[] jmc_files = Directory.GetFiles(_jmc_dir);

            StreamReader file;
            string line;
            

            for(int i = 0; i < jmc_files.Length; ++i)
            {
                file = new StreamReader
                    (jmc_files[i]                     ,
                     Encoding.GetEncoding("Shift_JIS"));

                while(file.Peek() >= 0)
                {
                    line = file.ReadLine();                    
                    analysis_line(line);
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
                m_mesh  = t_mesh.line_to_mesh_header(_line);
                return;
            }
            //    layer recode
            else if (t_layer.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.LAYER;
                m_layer = t_layer.line_to_layer_header(_line);
                return;
            }
            //    node recode
            else if (t_node.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.NODE;
                return;
            }
            else if (t_area.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.AREA;
                return;
            }
            //    line item recode
            else if (t_line.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.LINE;
                m_line = t_line.line_to_line_item(_line);
                return;
            }
            //    point recode
            else if (t_point.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.POINT;
                return;
            }
            
            //coordinate recode or note recode
            switch (m_layer.m_code)
            {
                case 1 :
                    if (m_prev_analysis == e_analysis_type.LINE)
                    {
                        m_prev_analysis = e_analysis_type.COORDINATE;
                        m_line.add_coordinate_point_record(_line);
                    }
                    else if(m_prev_analysis == e_analysis_type.AREA)
                    {
                        m_prev_analysis = e_analysis_type.CONSTRUCT_LINE;
                    }

                    return;

                case 2 :
                    m_prev_analysis = e_analysis_type.COORDINATE;
                    m_line.add_coordinate_point_record(_line);

                    return;

                case 3 :
                    m_prev_analysis = e_analysis_type.COORDINATE;
                    m_line.add_coordinate_point_record(_line);

                    return;

                case 5 :
                    m_prev_analysis = e_analysis_type.COORDINATE;
                    m_line.add_coordinate_point_record(_line);

                    return;

                case 7 :
                    return;
            }
            
            throw new FormatException("unknown string : " + _line);
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
        public static Encoding m_s_encode = Encoding.GetEncoding("shift_jis");
        private static t_xy<long> file_margin = new t_xy<long>(10000, 10000);

        /* member value and instance */
        //mesh
        private t_mesh  m_mesh;

        //layer
        private t_layer m_layer;

        //line item
        private t_line  m_line;

        //other
        private int             m_counter_mesh_recode;
        private int             m_counter_layer_recode;
        private int             m_counter_coordinate;
        private e_analysis_type m_prev_analysis;
    }
}
