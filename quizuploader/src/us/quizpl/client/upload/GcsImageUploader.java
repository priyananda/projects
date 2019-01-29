package us.quizpl.client.upload;

import us.quizpl.client.model.QuizPresentation;
import us.quizpl.client.model.QuizSlide;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

import com.google.cloud.WriteChannel;
import com.google.cloud.storage.BlobId;
import com.google.cloud.storage.BlobInfo;
import com.google.cloud.storage.Storage;
import com.google.cloud.storage.StorageOptions;

public class GcsImageUploader {
    private static final String BUCKET_NAME = "quizplus_storage";

    public void uploadQuiz(QuizPresentation quiz) {
    	Storage storage = StorageOptions.getDefaultInstance().getService();
		quiz.getSlides().forEach(
			(slide) -> {
				try {
					uploadSlide(storage, slide);
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			});
	}

	private void uploadSlide(Storage storage, QuizSlide slide) throws IOException {
		BlobId blobId = BlobId.of(BUCKET_NAME, slide.getCanonicalName());
		BlobInfo blobInfo = BlobInfo.newBuilder(blobId).setContentType("image/png").build();
		try(WriteChannel writer = storage.writer(blobInfo)) {
			try(RandomAccessFile file = new RandomAccessFile(slide.getLocalImagePath(), "r")){
				MappedByteBuffer fileData = file.getChannel().map(FileChannel.MapMode.READ_ONLY, 0, file.length());
				writer.write(fileData);
			}
		}
	}
}
