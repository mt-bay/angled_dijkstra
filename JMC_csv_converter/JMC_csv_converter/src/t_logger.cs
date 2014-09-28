using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


namespace JMC_csv_converter.src
{
    class t_logger
    {
        /* constructor */
        /// <summary>
        /// default constructor
        /// make log file and directory
        /// </summary>
        private t_logger()
        {
            try
            {
                //make directory
                if (!Directory.Exists(M_LOG_DIR))
                {
                    Directory.CreateDirectory(M_LOG_DIR);
                }

                //make log file
                string  date_format = "yymmdd_hhmm";
                DateTime now = DateTime.Now;
                m_path = M_LOG_DIR + now.ToString(date_format) + @".log";
                m_writer = new StreamWriter(m_path                           ,
                                            false                            , 
                                            Encoding.GetEncoding(M_CHAR_CODE));
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
                Console.ReadKey();
            }
        }


        /* static method */
        /// <summary>
        /// get singleton instance
        /// </summary>
        /// <returns></returns>
        public static t_logger get_instance()
        {
            return m_instance;
        }


        /* method */
        /// <summary>
        /// write contents
        /// </summary>
        /// <param name="_content">writeing contents</param>
        public void write(string _content)
        {
            m_writer.WriteLine(_content);
            m_writer.Flush();
        }

        /// <summary>
        /// write exception stack trace
        /// </summary>
        /// <param name="e">throwed exception</param>
        public void write_exception(Exception e)
        {
            m_writer.WriteLine(e.StackTrace);
            m_writer.Flush();
        }

        /// <summary>
        /// write info
        /// </summary>
        /// <param name="_contents">info</param>
        public void write_info(string _contents)
        {
            write_with_status(_contents, "info");
        }

        /// <summary>
        /// write warning info
        /// </summary>
        /// <param name="_contents">warning info</param>
        public void write_warning(string _contents)
        {
            write_with_status(_contents, "warning");
        }

        /// <summary>
        /// write fatal info
        /// </summary>
        /// <param name="_contents">fatal info</param>
        public void write_fatal(string _contents)
        {
            write_with_status(_contents, "fatal");
        }

        

        /// <summary>
        /// write with status
        /// </summary>
        /// <param name="_contents">writing contents</param>
        /// <param name="_status">contents status</param>
        private void write_with_status(string _contents, string _status)
        {
            string[] lines 
                        = _contents.Split(Environment.NewLine.ToCharArray());

            for (int i = 0; i < lines.Length; ++i)
            {
                lines[i].Replace(Environment.NewLine, @"");
            }

            m_writer.WriteLine(_status + @" : " + lines[0]);
            for (int i = 1; i < lines.Length; ++i)
            {
                
                for (int j = 0; j < _status.Length + 3; ++j)
                {
                    m_writer.Write(@" ");
                }
                m_writer.WriteLine(lines[i]);
            }
            m_writer.Flush();
        }


        /* const value */
        private const string M_CHAR_CODE = @"utf-8";
        private const string M_LOG_DIR   = @"log\";

        /* member value and instance */
        private static t_logger     m_instance = new t_logger();

        private string       m_path;
        private StreamWriter m_writer;
    }
}
