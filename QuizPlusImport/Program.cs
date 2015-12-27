using Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Us.QuizPl
{
    class Program
    {
        static void Main(string[] args)
        {
            Command command = CommandFactory.Parse(args);
            if (command != null)
                command.Execute();
        }
    }
}
