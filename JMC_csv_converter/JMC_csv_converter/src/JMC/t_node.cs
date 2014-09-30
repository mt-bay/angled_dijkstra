using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;


namespace JMC_csv_converter.src.JMC
{
    class t_node
    {
        /* static variable and instance */
        public static Regex m_recode_type
                        = new Regex(@"^N\s",
                                    RegexOptions.Compiled);
    }
}
