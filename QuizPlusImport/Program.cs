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
        private const string CONNECTION_URL = "http://localhost:8888/import";

        static void Main(string[] args)
        {
            Dictionary<string, object> slideProperties = new Dictionary<string, object>();
            slideProperties.Add("Name", "Slide7");
            slideProperties.Add("DocName", "Quiz 117");
            slideProperties.Add("Author", "Priyananda");
            slideProperties.Add("ImageURL", "http://a.com/b.jpg");
            string jsonData = JsonParser.ToJson(slideProperties);

            StringBuilder builder = new StringBuilder();
            builder.Append("slide=");
            builder.Append(WebUtility.UrlEncode(jsonData));

            HttpWebRequest request = (HttpWebRequest) HttpWebRequest.Create(CONNECTION_URL);
            request.Method = "POST";

            byte[] data = Encoding.ASCII.GetBytes(builder.ToString());

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
                        Console.WriteLine(myStreamReader.ReadToEnd());
                    }
                }
            }
        }
    }
}
