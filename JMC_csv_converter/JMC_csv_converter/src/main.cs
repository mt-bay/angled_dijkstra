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
                t_JMC   jmc   = new t_JMC(@"JMCマップ\DATA\");
                t_graph graph = jmc.to_graph();
                graph.to_csv(@"location.csv", @"adj.csv");
            }
            catch(Exception e)
            {
                t_logger.get_instance().write_exception(e);
                Console.WriteLine("catch in Main");
                Console.WriteLine("please look log file");
            }
            finally
            {
                Console.WriteLine();
                Console.WriteLine("wait key.");
                Console.ReadKey();
            }
            
        }
    }
}
