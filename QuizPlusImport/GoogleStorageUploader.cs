using Google.Apis.Http;
using Google.Apis.Storage.v1;
using Google.Apis.Auth.OAuth2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Google.Apis.Services;
using GSD = Google.Apis.Storage.v1.Data;
using System.IO;
using Google.Apis.Requests;

namespace Us.QuizPl
{
    class GoogleStorageUploader
    {
        public void UploadQuiz(QuizDocument doc)
        {
            var credential = GetCredentials();
            StorageService service = new StorageService(
                new BaseClientService.Initializer()
                {
                    HttpClientInitializer = credential,
                    ApplicationName = "Quiz Plus Uploader",
                });

            foreach(var slide in doc.Slides)
            {
                var fileobj = new GSD.Object() { Name = slide.CanonicalName };
                var uploadStream = new FileStream(slide.ImagePath, FileMode.Open, FileAccess.Read);
                var uploadRequest = service.Objects.Insert(
                    fileobj,
                    BUCKET_NAME,
                    uploadStream,
                    "image/jpeg");

                var task = uploadRequest.UploadAsync();
                task.ContinueWith(t =>
                {
                    // Remeber to clean the stream.
                    uploadStream.Dispose();
                });
            }
        }

        private IConfigurableHttpClientInitializer GetCredentials()
        {
            GoogleCredential credential = GoogleCredential.GetApplicationDefaultAsync().Result;
            if (credential.IsCreateScopedRequired)
            {
                credential = credential.CreateScoped(new[] {
                    StorageService.Scope.DevstorageReadWrite
                });
            }
            return credential;
        }

        private const string PROJECT_NAME = "quizplus-1145";
        private const string BUCKET_NAME = "quizplus_storage";
    }
}
