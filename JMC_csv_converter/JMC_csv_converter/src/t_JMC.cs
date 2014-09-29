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
            prev_analysis = e_analysis_type.NONE;
        }

        public t_graph jmc_dat_directory_to_graph(string _jmc_dir)
        {
            t_xy<long> margin = new t_xy<long>(0, 0);
            t_graph    result = new t_graph();

            string[] jmc_files = Directory.GetFiles(_jmc_dir);

            StreamReader file;
            string line;
            

            for(int i = 0; i < jmc_files.Length; ++i)
            {
                file = new StreamReader
                    (_jmc_dir + jmc_files[i]          ,
                     Encoding.GetEncoding("Shift_JIS"));

                while(file.Peek() >= 0)
                {
                    line = file.ReadLine();
                    analysis_line(line);
                }
            }

            return result;
        }

        private void analysis_line(string _line)
        {
            //recode type check
            //    mesh recode
            if (t_mesh.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.MESH;
                m_mesh  = t_mesh.line_to_mesh_header(_line);
                return;
            }
            //    layer recode
            if (t_layer.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.LAYER;
                m_layer = t_layer.line_to_layer_header(_line);
                return;
            }
            //    line item recode
            if (t_line_item.m_recode_type.IsMatch(_line))
            {
                m_prev_analysis = e_analysis_type.LINE_ITEM;
                m_line_item = t_line_item.line_to_line_item(_line);
                return;
            }
            //    

            
        }
        

        /* member enum */
        private enum e_analysis_type
        {
            NONE      ,
            MESH      ,
            LAYER     ,
            LINE_ITEM ,
            COORDINATE,
        }


        /* static value and instance */
        private static t_xy<long> file_margin = new t_xy<long>(10000, 10000);


        /* member value and instance */
        //mesh
        private t_mesh      m_mesh;

        //layer
        private t_layer     m_layer;

        //line item
        private t_line_item m_line_item;

        //other
        private int             m_counter_mesh_recode;
        private int             m_counter_layer_recode;
        private int             m_counter_coordinate;
        private e_analysis_type m_prev_analysis;
    }
}
