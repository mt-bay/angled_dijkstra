using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace JMC_csv_converter.src.JMC
{
    class t_line
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// build empty line item
        /// </summary>
        public t_line()
        {
            m_coordinate = new List<t_xy<int> >();
        }


        /* static method */
        /// <summary>
        /// generate line item by line item record
        /// </summary>
        /// <param name="_line"></param>
        /// <returns></returns>
        public static t_line line_to_line_item(string _line)
        {
            t_line result = new t_line();
            string elm;

            //recode type check
            elm = util.str_byte_substring(_line,  0,  2, t_JMC.m_s_encode);
            if (! m_recode_type.IsMatch(elm))
            {
                throw new FormatException
                            (@"invalid recode type");
            }

            //get layer code
            elm = util.str_byte_substring(_line,  2,  2, t_JMC.m_s_encode);
            switch (Int32.Parse(elm))
            {
                case 1 :
                    result.m_layer_code = 1;
                    break;

                case 2 :
                    result.m_layer_code = 2;
                    break;

                case 3 :
                    result.m_layer_code = 3;
                    break;

                case 5 :
                    result.m_layer_code = 5;
                    break;

                default :
                    throw new FormatException
                                (@"invalid layer code");
            }

            //get data item code
            elm = util.str_byte_substring(_line,  4,  2, t_JMC.m_s_encode);
            switch (result.m_layer_code)
            {
                case 1 :
                    switch (Int32.Parse(elm))
                    {
                        case 1 :
                            result.m_item_code = 1;
                            break;

                        case 2 :
                            result.m_item_code = 2;
                            break;

                        case 3 :
                            result.m_item_code = 3;
                            break;

                        case 4 :
                            result.m_item_code = 4;
                            break;

                        case 5 :
                            result.m_item_code = 5;
                            break;

                        case 9 :
                            result.m_item_code = 9;
                            break;
                        default :
                            throw new FormatException
                                        (@"invalid line code");
                    }
                    break;
                case 2 :
                    switch (Int32.Parse(elm))
                    {
                        case 1 :
                            result.m_item_code = 1;
                            break;

                        case 2 :
                            result.m_item_code = 2;
                            break;

                        case 3 :
                            result.m_item_code = 3;
                            break;

                        case 4 :
                            result.m_item_code = 4;
                            break;

                        case 5 :
                            result.m_item_code = 5;
                            break;

                        default :
                            throw new FormatException
                                        (@"invalid line code");
                    }
                    break;

                case 3 :
                    switch (Int32.Parse(elm))
                    {
                        case 1 :
                            result.m_item_code = 1;
                            break;

                        case 2 :
                            result.m_item_code = 2;
                            break;

                        case 3 :
                            result.m_item_code = 3;
                            break;

                        case 9 :
                            result.m_item_code = 9;
                            break;

                        default :
                            throw new FormatException
                                        (@"invalid line code");
                    }
                    break;

                case 5 :
                    switch (Int32.Parse(elm))
                    {
                        case 1 :
                            result.m_item_code = 1;
                            break;

                        case 2 :
                            result.m_item_code = 2;
                            break;

                        default :
                            throw new FormatException
                                        (@"invalid line code");
                    }
                    break;

                default :
                    throw new FormatException
                                (@"invalid layer code");
            }

            //get line series number
            elm = util.str_byte_substring(_line,  6,  5, t_JMC.m_s_encode);
            result.m_series_number = Int32.Parse(elm);

            //get line classification code
            elm = util.str_byte_substring(_line, 11,  6, t_JMC.m_s_encode);
            switch (result.m_layer_code)
            {
                case 1 :
                    switch (Int32.Parse(elm))
                    {
                        case 0 :
                            result.m_classification_code = 0;
                            break;

                        case 1 :
                            result.m_classification_code = 1;
                            break;

                        case 2 :
                            result.m_classification_code = 2;
                            break;

                        case 9 :
                            result.m_classification_code = 9;
                            break;

                        default :
                            throw new FormatException
                                        ("invalid classification code");
                    }
                    break;

                case 2 :
                    switch (Int32.Parse(elm))
                    {
                        case 0 :
                            result.m_classification_code = 0;
                            break;

                        case 1 :
                            result.m_classification_code = 1;
                            break;

                        default :
                            throw new FormatException
                                        ("invalid classification code");
                    }
                    break;

                case 3 :
                    switch (Int32.Parse(elm))
                    {
                        case 0 :
                            result.m_classification_code = 0;
                            break;

                        case 1 :
                            result.m_classification_code = 1;
                            break;

                        default :
                            throw new FormatException
                                        ("invalid classification code");
                    }
                    break;

                case 5 :
                    switch (Int32.Parse(elm))
                    {
                        case 0 :
                            result.m_classification_code = 0;
                            break;

                        case 1 :
                            result.m_classification_code = 1;
                            break;

                        default :
                            throw new FormatException
                                        ("invalid classification code");
                    }
                    break;

                default :
                    throw new FormatException
                                (@"invalid layer code");
            }

            //get src. node number
            elm = util.str_byte_substring(_line, 17,  5, t_JMC.m_s_encode);
            result.m_src_node_number = Int32.Parse(elm);

            //get src. adjacency infomation
            elm = util.str_byte_substring(_line, 22,  1, t_JMC.m_s_encode);
            result.m_src_adjacency_info = Int32.Parse(elm);

            //get dst. node number
            elm = util.str_byte_substring(_line, 23,  5, t_JMC.m_s_encode);
            result.m_dst_node_number = Int32.Parse(elm);

            //get dst. adjacency infomation
            elm = util.str_byte_substring(_line, 28,  1, t_JMC.m_s_encode);
            result.m_dst_adjacency_info = Int32.Parse(elm);

            //get left administrative code
            elm = util.str_byte_substring(_line, 29,  5, t_JMC.m_s_encode);
            result.m_left_administrative_code
                = (result.m_src_adjacency_info == 0)?               0 :
                                                      Int32.Parse(elm);

            //get right administrative code
            elm = util.str_byte_substring(_line, 34,  5, t_JMC.m_s_encode);
            result.m_right_administrative_code
                = (result.m_dst_adjacency_info == 0)?               0 :
                                                      Int32.Parse(elm);

            //get num. of coordinate point and number of coordinate recode
            elm = util.str_byte_substring(_line, 39,  6, t_JMC.m_s_encode);
            result.m_num_coordinate = Int32.Parse(elm);
            result.m_num_coordinate_recode
                = (result.m_num_coordinate / 7) + 1;

            return result;
        }

        /// <summary>
        /// add coordinate by point record
        /// </summary>
        /// <param name="_line">string line</param>
        public void add_coordinate_point_record(string _line)
        {
            string[] elm = new string[2];
            for (int i = 0; i < 7; ++i)
            {
                elm[0] = util.str_byte_substring
                                (_line, i * 10    ,  5, t_JMC.m_s_encode);
                elm[1] = util.str_byte_substring
                                (_line, i * 10 + 5,  5, t_JMC.m_s_encode);

                if(elm[0] == "     " &&
                   elm[1] == "     ")
                {
                    return;
                }

                m_coordinate.Add(new t_xy<int>
                                        (((elm[0] == "     ")?
                                                            0 :
                                            Int32.Parse(elm[0])),
                                         ((elm[1] == "     ")?
                                                            0 :
                                            Int32.Parse(elm[1]))));
            }
        }


        /* static variable and instance */
        public static Regex m_recode_type
                        = new Regex(@"^L\s",
                                    RegexOptions.Compiled);


        /* member variable and instance */
        public int m_layer_code;
        public int m_item_code;
        public int m_series_number;
        public int m_classification_code;
        public int m_src_node_number;
        public int m_src_adjacency_info;
        public int m_dst_node_number;
        public int m_dst_adjacency_info;
        public int m_left_administrative_code;
        public int m_right_administrative_code;
        public int m_num_coordinate;
        public int m_num_coordinate_recode;
        public List<t_xy<int> > m_coordinate;
    }
}
