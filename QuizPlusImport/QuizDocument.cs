using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PPT = Microsoft.Office.Interop.PowerPoint;

namespace Us.QuizPl
{
    class QuizDocument
    {
        public string Name;
        public string Author;
        public List<QuizSlide> Slides = new List<QuizSlide>();
        public DateTime Date;

        public static QuizDocument Parse(string filePath)
        {
            QuizDocument doc = new QuizDocument();
            PPT.Application pptApp = new PPT.Application();
            PPT.Presentation ppt = pptApp.Presentations.Open(filePath);
            Directory.Delete(IMAGE_TEMP_PATH, true);
            ppt.SaveCopyAs(IMAGE_TEMP_PATH, Microsoft.Office.Interop.PowerPoint.PpSaveAsFileType.ppSaveAsJPG);
            doc.Name = Path.GetFileNameWithoutExtension(filePath);
            doc.Date = new DateTime(2011, 06, 01);
            
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

        private const string IMAGE_TEMP_PATH = @"c:\temp\images_ppt";
        private const string IMAGE_RESIZED_TEMP_PATH = @"c:\temp\images_ppt_resized";
    }
}
