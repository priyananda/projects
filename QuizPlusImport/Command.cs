using Mono.Options;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Us.QuizPl
{
    public enum Commands
    {
        Upload,
        Dump,
        ShowHelp
    }

    abstract class Command
    {
        public List<String> FilesList;
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
                Logger.Log("Extracting Quiz from file: {0}", filename);
                QuizDocument doc = QuizDocument.Parse(filename);
                if (this.Author != null)
                    doc.Author = this.Author;
                if (this.Name != null)
                    doc.Name = this.Name;
                if (this.DateAsString != null)
                    doc.Date = new DateTime(
                        Int32.Parse(this.DateAsString.Substring(0, 4)),
                        Int32.Parse(this.DateAsString.Substring(4, 2)),
                        Int32.Parse(this.DateAsString.Substring(6, 2))
                    );

                if (!UseTestServer && !SkipImageUpload)
                {
                    Logger.Log("Uploading Images for {0} ...", doc.Name);
                    var googleStorageClient = new GoogleStorageUploader();
                    googleStorageClient.UploadQuiz(doc);
                }

                Logger.Log("Uploading Data for {0} ...", doc.Name);
                var importClient = new ImporterClient();
                importClient.UseTestServer = this.UseTestServer;
                string docId = importClient.ImportQuizDocument(doc);

                if (this.DoBulkUpload)
                {
                    importClient.BulkImportQuizSlides(docId, doc);
                }
                else
                {
                    foreach (var slide in doc.Slides)
                    {
                        importClient.ImportQuizSlide(docId, slide);
                    }
                }
            }
        }

        public String Name;
        public String Author;
        public String DateAsString;
        public bool UseTestServer;
        public bool DoBulkUpload;
        public bool SkipImageUpload;
    }

    class ShowHelpCommand : Command
    {
        public override void Execute()
        {
            Console.WriteLine("Usage: qpimport [OPTIONS]+ filename...");
            Console.WriteLine("Uploads quiz files to Quiz+");
            Console.WriteLine();
            Console.WriteLine("Options:");
            Options.WriteOptionDescriptions(Console.Out);
        }

        public OptionSet Options;
    }

    class CommandFactory
    {
        public static Command Parse(String[] args)
        {
            // Upload: qpimport -u [-a <Author+Name>] [-n <Quiz+Name>] [-dt YYYYMMDD] [-t] [-s] [-b] filename...
            // Dump:   qpimport -d filename...
            // Help:   qimport  -h
            Commands whichCommand = Commands.Upload;
            String authorName = null;
            String quizDate = null;
            String quizName = null;
            bool useTestServer = false;
            bool useBulkUpload = false;
            bool skipImageUpload = false;

            OptionSet optionset = new OptionSet() {
                { "u|upload", v => whichCommand = Commands.Upload},
                { "d|dump", v => whichCommand = Commands.Dump},
                { "a|author=", v => authorName = v },
                { "n|name=", v => quizName = v },
                { "dt|date=", v => quizDate = v },
                { "t", v => useTestServer = true},
                { "h|help", v => whichCommand = Commands.ShowHelp},
                { "b|bulk", v => useBulkUpload = true},
                { "s|skipimage", v => skipImageUpload = true},
            };

            List<string> filenames;
            try
            {
                filenames = optionset.Parse(args);
            }
            catch (OptionException e)
            {
                Console.Write("qpimport: ");
                Console.WriteLine(e.Message);
                Console.WriteLine("Try `qpimport --help' for more information.");
                return null;
            }

            Command ret = null;
            switch(whichCommand)
            {
                case Commands.Dump:
                    ret = new DumpCommand();
                    break;
                case Commands.ShowHelp:
                    var showHelpCmd = new ShowHelpCommand();
                    showHelpCmd.Options = optionset;
                    ret = showHelpCmd;
                    break;
                case Commands.Upload:
                    var uploadCmd = new UploadCommand();
                    uploadCmd.Name = quizName;
                    uploadCmd.UseTestServer = useTestServer;
                    uploadCmd.Author = authorName;
                    uploadCmd.DateAsString = quizDate;
                    uploadCmd.DoBulkUpload = useBulkUpload;
                    uploadCmd.SkipImageUpload = skipImageUpload;
                    ret = uploadCmd;
                    break;
            }
            if (ret != null)
                ret.FilesList = filenames;
            return ret;
        }
    }
}
