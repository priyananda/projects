using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PPT = Microsoft.Office.Interop.PowerPoint;

namespace Us.QuizPl
{
    class QuizSlide
    {
        public int SlideIndex;
        public string ImagePath;
        public string Text;
        public QuizDocument QuizDoc;

        public static QuizSlide Parse(PPT.Slide pptSlide, string directory)
        {
            QuizSlide slide = new QuizSlide();
            slide.SlideIndex = pptSlide.SlideNumber;
            slide.ImagePath = Path.Combine(directory, "Slide" + slide.SlideIndex + ".jpg");
            StringBuilder builder = new StringBuilder();
            foreach(PPT.Shape shape in pptSlide.Shapes)
            {
                if (shape.HasTextFrame == Microsoft.Office.Core.MsoTriState.msoTrue && shape.TextFrame.HasText == Microsoft.Office.Core.MsoTriState.msoTrue)
                    builder.AppendLine(shape.TextFrame.TextRange.Text);
            }
            slide.Text = builder.ToString();
            return slide;
        }

        public string CanonicalName
        {
            get
            {
                return String.Format("{0}/{1}", QuizDoc.Name, Path.GetFileName(this.ImagePath));
            }
        }
    }
}
