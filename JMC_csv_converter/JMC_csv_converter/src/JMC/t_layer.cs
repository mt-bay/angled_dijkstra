﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;


namespace JMC_csv_converter.src.JMC
{
    class t_layer
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// </summary>
        public t_layer()
        {
            //nothing to do
        }


        /* static method */
        /// <summary>
        /// string line to layer header
        /// </summary>
        /// <param name="_line">header line</param>
        /// <returns>created layer header</returns>
        /// <exception cref="System.FormatException">
        /// invalid recode type or invalid layer code
        /// </exception>
        public static t_layer line_to_layer_header(string _line)
        {
            t_layer result = new t_layer();

            string elm;
            e_recode_type recode_type;

            //get header type
            elm = _line.Substring(0, 2);
            switch (elm)
            {
                case "H1":
                    recode_type = e_recode_type.H1;
                    break;
                case "H2":
                    recode_type = e_recode_type.H2;
                    break;
                default:
                    throw new FormatException
                        ("invalid recode type");
            }

            //get layer code
            elm = _line.Substring(2, 2);
            switch (elm)
            {
                case " 1":
                    result.m_code = 1;
                    break;
                case " 2":
                    result.m_code = 2;
                    break;
                case " 3":
                    result.m_code = 3;
                    break;
                case " 4":
                    result.m_code = 4;
                    break;
                case " 5":
                    result.m_code = 5;
                    break;
                default:
                    throw new FormatException
                        ("");
            }

            //get num of node
            elm = _line.Substring(4, 5);
            result.m_num_node = (recode_type == e_recode_type.H1) ?
                                                  0 :
                                    Int32.Parse(elm);

            //get num of line
            elm = _line.Substring(9, 5);
            result.m_num_line = Int32.Parse(elm);

            //get num of area
            elm = _line.Substring(14, 5);
            result.m_num_area = (recode_type == e_recode_type.H1) ?
                                                  0 :
                                    Int32.Parse(elm);

            //get num of point
            elm = _line.Substring(19, 5);

            //get num of recode
            elm = _line.Substring(24, 5);
            result.m_num_record = Int32.Parse(elm);

            return result;
        }


        /* member enum */
        /// <summary>
        /// recode type
        /// </summary>
        /// 
        private enum e_recode_type
        {
            H1, //non-structed layer
            H2, //structed layer
        }


        /* static variable and instance */
        public static Regex m_recode_type
                        = new Regex(@"^H[12]",
                                    RegexOptions.Compiled);


        /* member variable and instance */
        public int m_code;
        public int m_num_node;
        public int m_num_line;
        public int m_num_area;
        public int m_num_point;
        public int m_num_record;

        
    }
}
