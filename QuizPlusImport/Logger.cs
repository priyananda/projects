using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Us.QuizPl
{
    class Logger
    {
        public static void Log(String format, params Object[] args)
        {
            Log(String.Format(format, args));
        }
        public static void Log(String s)
        {
            if (s_streamWriter == null)
                InitLogFile();
            s_streamWriter.WriteLine(s);
            Console.WriteLine(s);
        }

        private static void InitLogFile()
        {
            s_streamWriter = new StreamWriter(DateTime.Today.ToString("yyyyMMdd-HHmm") + ".log");
            s_streamWriter.AutoFlush = true;
        }
        private static StreamWriter s_streamWriter;
    }
}
