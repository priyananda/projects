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
            Dictionary<string, object> presentationProperties = new Dictionary<string, object>();
            presentationProperties.Add("PresentationId", "5066549580791808");
            presentationProperties.Add("ImageURL", "http://ding.com/a.jpg");
            presentationProperties.Add("TextContent", "Nimmajji Pinda Loafer");
            string jsonData = JsonParser.ToJson(presentationProperties);

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
