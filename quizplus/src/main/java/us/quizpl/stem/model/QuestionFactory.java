package us.quizpl.stem.model;

import com.google.common.collect.ImmutableMap;

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
		.put("1", new Question("astronauts", 10))
		.put("2", new Question("zeus", 10))
		.put("3", new Question("satellites", 10))
		.put("4", new Question("aliens", 10))
		.put("5", new Question("thoreau", 15))
		.put("6", new Question("sulfur", 15))
		.put("7", new Question("oxygen", 15))
		.put("8", new Question("soylent", 15))
		.put("9", new Question("stem", 20))
		.put("10", new Question("", 20))
		.put("11", new Question("", 20))
		.put("12", new Question("", 20))
		.put("13", new Question("", 25))
		.put("14", new Question("", 25))
		.put("15", new Question("1984", 25))
		.put("16", new Question("", 25))
		.build();
	
	public static Question get(String key) {
		return QUESTIONS.get(key);
	}
}
