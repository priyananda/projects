package us.quizpl.mofc.model;

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
		.put("1", new Question("lovegood", 10))
		.put("2", new Question("sabertooth", 10))
		.put("3", new Question("cafeteria", 10))
		.put("4", new Question("library", 10))
		.put("5", new Question("byepluto", 15))
		.put("6", new Question("spaceforce", 15))
		.put("7", new Question("money", 15))
		.put("8", new Question("johnwoo", 15))
		.put("9", new Question("kirkland", 20))
		.put("10", new Question("victorian", 20))
		.put("11", new Question("harrisonford", 20))
		.put("12", new Question("pocahontas", 20))
		.put("13", new Question("pocahontas", 20))
		.put("14", new Question("pocahontas", 20))
		.put("15", new Question("pocahontas", 20))
		.put("16", new Question("pocahontas", 20))
		.build();
	
	public static Question get(String key) {
		return QUESTIONS.get(key);
	}
}
