package us.quizpl.halloween.model;

import com.google.common.collect.ImmutableMap;
import com.google.gson.JsonObject;

public class QuestionFactory {
	public static class Question {
		private final String answerPattern;
		private final int points;
		Question(String answerPattern, int points) {
			this.answerPattern = answerPattern;
			this.points = points;
		}
		public String getAnswerPattern() {
			return answerPattern;
		}
		public int getPoints() {
			return this.points;
		}
	}
	
	private static ImmutableMap<String, Question> QUESTIONS = new ImmutableMap.Builder<String, Question>()
		// Easy
		.put("mxpe", new Question("lovegood", 10)) // SCHOOL_OF_MAGIC
		.put("this", new Question("sabertooth", 10)) // MERLINS_BEARD
		.put("rnfa", new Question("cafeteria", 10)) // RANSOM_NOTE
		.put("dgez", new Question("library", 10)) // FOLLOWING_DIRECTIONS
		// Medium
		.put("ejsh", new Question("byepluto", 15)) // SOLAR_SORT
		.put("nvqw", new Question("spaceforce", 15)) // CALL_ME_MAYBE
		.put("mabc", new Question("money", 15)) // TRICK_TACK_TOE
		.put("vghd", new Question("johnwoo", 15)) // FACE_OFF
		// Hard
		.put("lurh", new Question("kirkland", 20)) // JAC_AND_JILL
		.put("gcfg", new Question("victorian", 20)) // ISBN
		.put("bwgs", new Question("harrisonford", 20)) // INDIANA_JONES
		.put("pahf", new Question("pocahontas", 20)) // ELEMENTARY
		.build();
	
	public static Question get(String key) {
		return QUESTIONS.get(key);
	}
}
