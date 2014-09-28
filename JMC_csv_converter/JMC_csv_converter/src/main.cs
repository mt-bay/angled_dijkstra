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
            }
            catch(Exception e)
            {
                t_logger.get_instance().write_exception(e);
            }
            Console.WriteLine("wait key.");
            Console.ReadKey();
        }
    }
}
