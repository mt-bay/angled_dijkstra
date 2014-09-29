﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace JMC_csv_converter.src.JMC
{
    class t_mesh
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// </summary>
        public t_mesh()
        {
            m_padding = new t_xy<long>();
        }


        /* static method */
        /// <summary>
        /// string line to mesh header
        /// </summary>
        /// <param name="_line">mesh line</param>
        /// <returns>created mesh</returns>
        /// <exception cref="System.FormatException">
        /// invalid recode type
        /// </exception>
        public static t_mesh line_to_mesh_header(string _line)
        {
            t_mesh result = new t_mesh();

            string elm;

            //recode type check
            elm = _line.Substring( 0,  2);
            if(! m_recode_type.IsMatch(elm))
            {
                throw new FormatException
                            ("invalid recode type");
            }

            //secondary mesh code to padding
            elm = _line.Substring( 2,  6);
            int mesh_code = Int32.Parse(elm);
            result.m_padding = new t_xy<long>
                            ((Int32.Parse(elm.Substring(0, 2))
                             * (SECONDARY_MESH_MAX + 1)
                             + Int32.Parse(elm.Substring(4, 1)))
                             * MESH_LOCATION_MAX_X              ,
                            (Int32.Parse(elm.Substring(2, 2))
                             * (SECONDARY_MESH_MAX + 1)
                             + Int32.Parse(elm.Substring(5, 1))
                             * MESH_LOCATION_MAX_Y             ));

            //get number or layer
            elm = _line.Substring(28,  3);
            result.m_num_layer = Int32.Parse(elm);

            //get number of recode
            elm = _line.Substring(51,  5);
            result.m_num_record = Int32.Parse(elm);

            return result;
        }


        /* const value */
        private const long SECONDARY_MESH_MAX  = 7;
        private const long MESH_LOCATION_MAX_X = 10000;
        private const long MESH_LOCATION_MAX_Y = 10000;


        /* static variable and instance */
        public static Regex m_recode_type
                        = new Regex(@"^M\s",
                                    RegexOptions.Compiled);


        /* member variable and instance */
        public int        m_num_record;
        public t_xy<long> m_padding;
        public int        m_num_layer;
    }
}