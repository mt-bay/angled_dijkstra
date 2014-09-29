using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace JMC_csv_converter.src.JMC
{
    class t_line_item
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// build empty line item
        /// </summary>
        public t_line_item()
        {
            m_coordinate = new List<t_xy<long> >();
        }


        /* static method */
        /// <summary>
        /// generate line item by line item record
        /// </summary>
        /// <param name="_line"></param>
        /// <returns></returns>
        public static t_line_item line_to_line_item(string _line)
        {
            t_line_item result = new t_line_item();
            string elm;

            //recode type check
            elm = _line.Substring(0, 2);
            if (m_recode_type.IsMatch(elm))
            {
                throw new FormatException
                            (@"invalid recode type");
            }

            //get layer code
            elm = _line.Substring( 2,  2);
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
            elm = _line.Substring( 4,  2);
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
            elm = _line.Substring( 6,  5);
            result.m_series_number = Int32.Parse(elm);

            //get line classification code
            elm = _line.Substring(11,  6);
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
            elm = _line.Substring(17,  5);
            result.m_src_node_number = Int32.Parse(elm);

            //get src. adjacency infomation
            elm = _line.Substring(22,  1);
            result.m_src_adjacency_info = Int32.Parse(elm);

            //get dst. node number
            elm = _line.Substring(23,  5);
            result.m_dst_node_number = Int32.Parse(elm);

            //get dst. adjacency infomation
            elm = _line.Substring(28,  1);
            result.m_dst_adjacency_info = Int32.Parse(elm);

            //get left administrative code
            elm = _line.Substring(29,  5);
            result.m_left_administrative_code = Int32.Parse(elm);

            //get right administrative code
            elm = _line.Substring(34,  5);
            result.m_right_administrative_code = Int32.Parse(elm);

            //get num. of coordinate point and number of coordinate recode
            elm = _line.Substring(39,  6);
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
                elm[0] = _line.Substring( i * 10     , 5);
                elm[1] = _line.Substring((i * 10) + 5, 5);

                if(elm[0] == "     " &&
                   elm[1] == "     ")
                {
                    return;
                }

                m_coordinate.Add(new t_xy<long>
                                        (((elm[0] == "     ")?
                                                            0 :
                                            Int64.Parse(elm[0])),
                                         ((elm[1] == "     ")?
                                                            0 :
                                            Int64.Parse(elm[1]))));
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
        public List<t_xy<long> > m_coordinate;
    }
}
