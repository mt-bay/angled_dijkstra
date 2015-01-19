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
            string jmc_dir       = (args.Length >= 1)?
                                        args[0] : @"DATA\";
            string p_graph_file = (args.Length >= 2)?
                                    args[1] : @"result\p_graph.csv";
            try
            {
                t_JMC   jmc   = new t_JMC(jmc_dir);
                t_logger.get_instance().write_info
                    ("number of coordinate : " + jmc.get_coordinate_num());

                t_p_graph p_graph = jmc.to_p_graph();

                p_graph.to_csv(p_graph_file);
                
                

                t_logger.get_instance().write(@"convert successful");
            }
            catch(Exception e)
            {
                t_logger.get_instance().write_exception(e);
                Console.WriteLine(@"catch in Main");
                Console.WriteLine(@"please look log file");
            }
            finally
            {
#if DEBUG
                Console.WriteLine();
                Console.WriteLine("wait key.");
                Console.ReadKey();
#endif
            }
            
        }
    }
}
