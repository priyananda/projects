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
    class ImporterClient
    {
        public string ImportQuizDocument(QuizDocument doc)
        {
            Dictionary<string, object> properties = new Dictionary<string, object>();
            properties.Add("Name", doc.Name);
            properties.Add("Date", doc.Date.ToShortDateString());
            properties.Add("Author", doc.Author);
            properties.Add("SlideCount", doc.Slides.Count);

            string docId = ExecuteImport(
                "presentation",
                properties
            );

            return docId;
        }

        public void ImportQuizSlide(string docId, QuizSlide slide)
        {
            Dictionary<string, object> properties = new Dictionary<string, object>();
            properties.Add("PresentationId", docId);
            properties.Add("ImageURL", slide.CanonicalName);
            properties.Add("TextContent", slide.Text.Replace("\"", "'"));

            ExecuteImport(
                "slide",
                properties
            );
        }

        private string ExecuteImport(string paramName, Dictionary<string, object> properties)
        {
            string jsonData = JsonParser.ToJson(properties);

            StringBuilder builder = new StringBuilder();
            builder.Append(paramName);
            builder.Append("=");
            builder.Append(WebUtility.UrlEncode(jsonData));
            byte[] data = Encoding.ASCII.GetBytes(builder.ToString());

            HttpWebRequest request = (HttpWebRequest) HttpWebRequest.Create(CONNECTION_URL);
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

        private const string CONNECTION_URL = "http://localhost:8888/import";
    }
}
