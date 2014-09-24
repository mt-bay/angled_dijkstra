using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JMC_csv_converter
{
    class main
    {
        static void Main(string[] args)
        {
            try
            {
                t_xy<int> test = new t_xy<int>(1, 2);
                t_xy<long> test_2 = new t_xy<long>(2, 1);

                Console.WriteLine(util_xy.length(test, test_2));
            }
            catch(Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
            Console.WriteLine("wait key.");
            Console.ReadKey();
        }
    }
}
