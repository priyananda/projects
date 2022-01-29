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
		.put("1", new Question("harry", 10))
		.put("2", new Question("starwars", 10))
		.put("3", new Question("baby", 10))
		.put("4", new Question("snowwhite", 10))
		.put("5", new Question("remote", 15))
		.put("6", new Question("kevin778", 15))
		.put("7", new Question("042", 15))
		.put("8", new Question("mickey", 15))
		.put("9", new Question("pickaxe", 20))
		.put("10", new Question(".*slope.*", 20))
		.put("11", new Question("battleroyale", 20))
		.put("12", new Question("notpluto", 20))
		.put("13", new Question("zircon", 20))
		.put("14", new Question("distribution", 20))
		.put("15", new Question("lwsd", 20))
		.put("16", new Question("capitals", 20))
		.put("17", new Question("agatha", 30))
		.build();
	
	public static Question get(String key) {
		return QUESTIONS.get(key);
	}
}
