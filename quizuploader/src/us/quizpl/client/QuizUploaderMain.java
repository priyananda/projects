package us.quizpl.client;

import com.google.devtools.common.options.OptionsParser;

import us.quizpl.client.model.QuizBuilder;
import us.quizpl.client.model.QuizPresentation;
import us.quizpl.client.upload.GcsImageUploader;
import us.quizpl.client.upload.QuizModelUploader;

public class QuizUploaderMain {
	public static void main(String[] args)  throws Exception {
		OptionsParser parser = OptionsParser.newOptionsParser(UploadOptions.class);
	    parser.parseAndExitUponError(args);
	    UploadOptions options = parser.getOptions(UploadOptions.class);
    
	    QuizPresentation quiz = new QuizBuilder().setOptions(options).build();

	    logQuiz(quiz);
	    
	    if (!options.skipImageUpload) {
	    	new GcsImageUploader().uploadQuiz(quiz);
	    }
	    new QuizModelUploader(options.server).uploadQuiz(quiz);
	}

	private static void logQuiz(QuizPresentation quiz) {
		System.out.println(String.format("Name:%s, Author:%s, Date:%s",
			quiz.getName(), quiz.getAuthor(), quiz.getDate()));
		quiz.getSlides().forEach((slide) -> {
			System.out.println(String.format("   Id:%d, CanonicalName:%s, LocalPath:%s",
				slide.getSlideIndex(), slide.getCanonicalName(), slide.getLocalImagePath()));
		});
	}
}
