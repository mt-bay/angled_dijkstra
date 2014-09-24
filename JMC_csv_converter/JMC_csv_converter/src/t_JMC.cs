using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;


namespace JMC_csv_converter.src
{
    /// <summary>
    /// JMC io class
    /// </summary>
    class t_JMC
    {
        private static t_xy<long> file_margin = new t_xy<long>(10000, 10000);

        /* constructor */
        /// <summary>
        /// default constructor
        /// built empty t_JMC
        /// </summary>
        public t_JMC()
        {

        }

        public static t_graph jmc_dat_directory_to_graph(string _jmc_dir)
        {
            t_xy<long> margin = new t_xy<long>(0, 0);
            t_graph result = new t_graph();

            string[] jmc_files = Directory.GetFiles(_jmc_dir);

            StreamReader jmc;
            string line;

            for(int i = 0; i < jmc_files.Length; ++i)
            {
                jmc = new StreamReader
                    (_jmc_dir + jmc_files[i]          ,
                     Encoding.GetEncoding("Shift_JIS"));

                while(jmc.Peek() >= 0)
                {
                    line = jmc.ReadLine();

                }
            }

            return result;
        }

        private void analysis_line(string _line)
        {
            string elm;
            //recode type check
            elm = _line.Substring(0, 2);
            if(elm != "M ")
            {
                return;
            }

        }

        private void analysis_mesh_header(string _line)
        {
            string elm;
            
            //secondary mesh code to padding
            elm = _line.Substring(2, 6);
            int mesh_code = Int32.Parse(elm);
            m_padding = new t_xy<long>
                        ((Int32.Parse(elm.Substring(0, 2))
                        * (SECONDARY_MESH_MAX + 1)
                        + Int32.Parse(elm.Substring(4, 1)))
                        * MESH_LOCATION_MAX_X              ,
                         (Int32.Parse(elm.Substring(2, 2))
                        * (SECONDARY_MESH_MAX + 1)
                        + Int32.Parse(elm.Substring(5, 1))
                        * MESH_LOCATION_MAX_Y             ));

            //get number or layer
            elm = _line.Substring(28, 3);
            m_num_of_layer = Int32.Parse(elm);

            //get number of recode
            elm = _line.Substring(51, 5);
            m_num_of_record = Int32.Parse(elm);

            
        }

        /* const value and instance */
        private const long SECONDARY_MESH_MAX  = 7;
        private const long MESH_LOCATION_MAX_X = 10000;
        private const long MESH_LOCATION_MAX_Y = 10000;


        /* member value and instance */
        private t_xy<long> m_padding;
        enum header_type : int
        {

        }
        private int m_num_of_layer;
        private int m_num_of_record;

        private Regex m_reg_mesh_header
                        = new Regex(@"^M\s"            ,
                                    RegexOptions.Compiled);
        private Regex m_reg_layer_header
                        = new Regex(@"^H[12]",
                                    RegexOptions.Compiled);

    }
}
