using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using PPT = Microsoft.Office.Interop.PowerPoint;

namespace Us.QuizPl
{
    class QuizDocument
    {
        public string Name;
        public string Author;
        public List<QuizSlide> Slides = new List<QuizSlide>();
        public DateTime Date;

        /*
        public static QuizDocument Parse(string filePath)
        {
            QuizDocument doc = new QuizDocument();
            PPT.Application pptApp = new PPT.Application();
            PPT.Presentation ppt = pptApp.Presentations.Open(filePath);
            Directory.Delete(IMAGE_TEMP_PATH, true);
            //ppt.SaveCopyAs(IMAGE_TEMP_PATH, Microsoft.Office.Interop.PowerPoint.PpSaveAsFileType.ppSaveAsJPG);
            doc.ExtractDetails(filePath);
            
            foreach (PPT.Slide pptSlide in ppt.Slides)
            {
                QuizSlide docSlide = QuizSlide.Parse(pptSlide, IMAGE_TEMP_PATH);
                docSlide.QuizDoc = doc;
                doc.Slides.Add(docSlide);
                ImageHelper.ResaveImage(docSlide.ImagePath, 0.5m, IMAGE_RESIZED_TEMP_PATH);
                docSlide.ImagePath = docSlide.ImagePath.Replace(IMAGE_TEMP_PATH, IMAGE_RESIZED_TEMP_PATH);
            }
            ppt.Close();
            pptApp.Quit();

            return doc;
        }
        */

        public static QuizDocument Parse(string directory)
        {
            QuizDocument doc = new QuizDocument();
            doc.ExtractDetails(directory);

            string[] files = Directory.GetFiles(directory);
            for (int slideIndex = 1; slideIndex <= files.Length; ++slideIndex)
            {
                QuizSlide docSlide = QuizSlide.Parse(slideIndex, directory);
                docSlide.QuizDoc = doc;
                doc.Slides.Add(docSlide);
            }
            return doc;
        }

        public void SetDate(string dateAsString)
        {
            this.Date = new DateTime(
                Int32.Parse(dateAsString.Substring(0, 4)),
                Int32.Parse(dateAsString.Substring(4, 2)),
                Int32.Parse(dateAsString.Substring(6, 2))
            );
        }

        private void ExtractDetails(string filePath)
        {
            String filename = Path.GetFileNameWithoutExtension(filePath);
            string[] parts = filename.Split('.');
            if (parts != null && parts.Length == 3)
            {
                this.Name = parts[0];
                this.Author = parts[1];
                SetDate(parts[2]);
            }
        }

        private const string IMAGE_TEMP_PATH = @"c:\temp\images_ppt";
        private const string IMAGE_RESIZED_TEMP_PATH = @"c:\temp\images_ppt_resized";
    }
}
