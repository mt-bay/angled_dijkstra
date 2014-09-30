using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter.src
{
    class main
    {
        static void Main(string[] args)
        {
            try
            {

                t_JMC jmc = new t_JMC();
                jmc.jmc_dat_directory_to_graph(@"JMCマップ\DATA\");

            }
            catch(Exception e)
            {
                Console.WriteLine("catch in Main");
                Console.WriteLine("please look log file");
                t_logger.get_instance().write_exception(e);
                Console.WriteLine();
                Console.WriteLine("wait key.");
                Console.ReadKey();
            }
        }
    }
}
