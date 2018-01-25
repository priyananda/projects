using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Us.QuizPl
{
    class ImporterClient
    {
        public bool UseTestServer { get; set; }

        public string ImportQuizDocument(QuizDocument doc)
        {
            Logger.Log("Importing Document {0} ...", doc.Name);

            Dictionary<string, object> properties = SerializeDoc(doc);
            StringBuilder builder = new StringBuilder();
            BuildData(builder, "presentation", properties);
            string docId = ExecuteImport(builder.ToString());

            Logger.Log("Document Imported with docId: {0}", docId);

            return docId;
        }

        private Dictionary<string, object> SerializeDoc(QuizDocument doc)
        {
            Dictionary<string, object> properties = new Dictionary<string, object>();
            properties.Add("name", doc.Name);
            properties.Add("date", doc.Date.ToShortDateString());
            properties.Add("author", doc.Author);
            properties.Add("slidecount", doc.Slides.Count);
            return properties;
        }

        private Dictionary<string, object> SerializeSlide(string docId, QuizSlide slide)
        {
            Dictionary<string, object> properties = new Dictionary<string, object>();
            properties.Add("presentationid", docId);
            properties.Add("imageurl", slide.CanonicalName);
            properties.Add("textcontent", slide.Text.Replace("\"", "'"));
            properties.Add("slideindex", slide.SlideIndex.ToString());
            return properties;
        }

        public void ImportQuizSlide(string docId, QuizSlide slide)
        {
            Logger.Log("Import Slide {0} of document {1}", slide.SlideIndex, docId);

            Dictionary<string, object> properties = SerializeSlide(docId, slide);
            StringBuilder builder = new StringBuilder();
            BuildData(builder, "slide", properties);
            string slideResult = ExecuteImport(builder.ToString());

            Logger.Log(slideResult);
        }

        public void BulkImportQuizSlides(string docId, QuizDocument doc)
        {
            StringBuilder builder = new StringBuilder();

            foreach(var slide in doc.Slides)
            {
                Logger.Log("Import Slide {0} of document {1}", slide.SlideIndex, docId);
                Dictionary<string, object> properties = SerializeSlide(docId, slide);
                BuildData(builder, "slide", properties);
                builder.Append("&");
            }
            string slideResult = ExecuteImport(builder.ToString());
            Logger.Log(slideResult);
        }

        private void BuildData(StringBuilder builder, string paramName, Dictionary<string, object> properties)
        {
            string jsonData = JsonConvert.SerializeObject(properties, Formatting.None);
            builder.Append(paramName);
            builder.Append("=");
            builder.Append(WebUtility.UrlEncode(jsonData));
        }

        private string ExecuteImport(string dataAsString)
        {
            byte[] data = Encoding.ASCII.GetBytes(dataAsString);
            HttpWebRequest request = (HttpWebRequest) HttpWebRequest.Create(
                this.UseTestServer ? CONNECTION_URL_TEST : CONNECTION_URL_PROD);
            request.Method = "POST";
            request.ContentType = "application/x-www-form-urlencoded";
            request.ContentLength = data.Length;

            var requestStream = request.GetRequestStream();
            requestStream.Write(data, 0, data.Length);
            requestStream.Close();

            using (var myHttpWebResponse = (HttpWebResponse)request.GetResponse())
            {
                using (var responseStream = myHttpWebResponse.GetResponseStream())
                {
                    using (var myStreamReader = new StreamReader(responseStream, Encoding.Default))
                    {
                        return myStreamReader.ReadToEnd();
                    }
                }
            }
        }

        private const string CONNECTION_URL_TEST = "http://localhost:8080/import";
        private const string CONNECTION_URL_PROD = "http://quizpl.us/import";
    }
}
