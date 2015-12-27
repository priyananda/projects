using Google.Apis.Http;
using Google.Apis.Storage.v1;
using Google.Apis.Auth.OAuth2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Google.Apis.Services;
using Google.Apis.Storage.v1.Data;
using System.IO;

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
                var fileobj = new Google.Apis.Storage.v1.Data.Object()
                {
                    Name = slide.CanonicalName
                };
                service.Objects.Insert(
                    fileobj,
                    BUCKET_NAME,
                    new FileStream(slide.ImagePath, FileMode.Open, FileAccess.Read),
                    "image/jpeg").Upload();

                var req = service.Objects.Get(BUCKET_NAME, fileobj.Name);
                fileobj = req.Execute();
                Logger.Log("\tUploaded {0} as {1} MediaLink: {2}, SelfLink: {3} ",
                    Path.GetFileName(slide.ImagePath), fileobj.Name, fileobj.MediaLink, fileobj.SelfLink);
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
