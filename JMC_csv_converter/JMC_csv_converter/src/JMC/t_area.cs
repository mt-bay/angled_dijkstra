using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;


namespace JMC_csv_converter.src.JMC
{
    class t_area
    {

        /* static variable and instance */
        public static Regex m_recode_type
                        = new Regex(@"^A\s",
                                    RegexOptions.Compiled);
    }
}
