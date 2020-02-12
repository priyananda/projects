package us.quizpl.client.model;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import us.quizpl.client.UploadOptions;

public class QuizBuilder {
	private UploadOptions options;
	
	public QuizBuilder setOptions(UploadOptions options) {
		this.options = options;
		return this;
	}
	
	public QuizPresentation build() throws Exception {
		QuizPresentation quiz = QuizPresentation.create(
			options.quizName, options.authorName, options.dateAsString);
		Path folderPath = Paths.get(options.inputPath);
		if (!Files.exists(folderPath)) {
			throw new Exception("Input folder doesn't exist");
		}
		if (!Files.isDirectory(folderPath)) {
			throw new Exception("Input folder isn't a directory");
		}
		Files.walk(folderPath)
			.filter(Files::isRegularFile)
			.sorted()
			.forEach((filePath) -> {
				quiz.addSlide(buildSlide(quiz, filePath));
			});
		return quiz;
	}

	private static QuizSlide buildSlide(QuizPresentation quiz, Path filePath) {
		int slideIndex = Integer.parseInt(
			filePath.getFileName().toString().replace("Slide - ", "").replace(".jpg", ""));
		QuizSlide slide = QuizSlide.create(quiz, slideIndex, "", filePath.toString());
		return slide;
	}
}
