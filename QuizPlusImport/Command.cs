using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Us.QuizPl
{
    abstract class Command
   {
        public List<String> FilesList = new List<string>();
        public abstract void Execute();
    }

    class DumpCommand : Command
    {
        public override void Execute()
        {
            foreach(var filename in FilesList)
            {
                QuizDocument doc = QuizDocument.Parse(filename);
                Console.WriteLine(doc.Name);
                foreach(var slide in doc.Slides)
                {
                    Console.WriteLine("\tIndex:{0}\n\tPath:{1}\n\tText:{2}", slide.SlideIndex, slide.ImagePath, slide.Text);
                }
            }
        }
    }

    class UploadCommand : Command
    {
        public override void Execute()
        {
            foreach (var filename in FilesList)
            {
                QuizDocument doc = QuizDocument.Parse(filename);
                doc.Author = "Priyananda";
                Console.WriteLine("Uploading Images for {0} ...", doc.Name);
                //new GoogleStorageUploader().UploadQuiz(doc);
                Console.WriteLine("Uploading Data for {0} ...", doc.Name);

                var importClient = new ImporterClient();
                string docId = importClient.ImportQuizDocument(doc);
                foreach (var slide in doc.Slides)
                {
                    importClient.ImportQuizSlide(docId, slide);
                    break;
                }
            }
        }
    }

    class CommandFactory
    {
        public static Command Parse(String[] args)
        {
            Command ret = null;
            switch (args[0])
            {
                case "dump": ret = new DumpCommand(); break;
                case "upload": ret = new UploadCommand(); break;
                default:
                    ret = new UploadCommand();
                    ret.FilesList.Add(args[0]);
                    break;

            }
            for(int i = 1; i < args.Length; ++i)
                ret.FilesList.Add(args[i]);
            return ret;
        }
    }
}
