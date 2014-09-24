using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    class t_JMC
    {
        private static t_xy<long> file_margin = new t_xy<long>(10000, 10000);

        public static t_graph jmc_dat_directory_to_graph(string _jmc_dir)
        {
            t_xy<long> margin = new t_xy<long>(0, 0);
            t_graph result = new t_graph();

            string[] jmc_files = Directory.GetFiles(_jmc_dir);

            StreamReader jmc;

            for(int i = 0; i < jmc_files.Length; ++i)
            {
                jmc = new StreamReader
                    (_jmc_dir + jmc_files[i], Encoding.GetEncoding("Shift_JIS"));

                
            }

            return result;
        }


    }
}
