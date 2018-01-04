package us.quizpl;

import com.google.appengine.api.blobstore.BlobKey;
import com.google.appengine.api.blobstore.BlobstoreService;
import com.google.appengine.api.blobstore.BlobstoreServiceFactory;
import com.google.appengine.api.images.ImagesServiceFactory;
import com.google.appengine.api.images.ServingUrlOptions;

public class StorageHelper {
	public static String getUrlForGcsFile(String bucketName, String fileName) {
		BlobstoreService blobstoreService = BlobstoreServiceFactory.getBlobstoreService();
		BlobKey blobKey = blobstoreService.createGsBlobKey("/gs/" + bucketName + "/" + fileName);
		ServingUrlOptions options = ServingUrlOptions.Builder.withBlobKey(blobKey);
		try {
			String url = ImagesServiceFactory.getImagesService().getServingUrl(options);
			return url;
		} catch(Exception e) {
			return fileName;
		}
	}
}
