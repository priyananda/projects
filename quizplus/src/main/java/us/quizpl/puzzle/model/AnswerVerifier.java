package us.quizpl.puzzle.model;

import java.util.function.Consumer;
import java.util.regex.Pattern;

import com.google.gson.JsonObject;

public class AnswerVerifier {
	public static JsonObject check(CompanyLevel clevel, String answer, Consumer<CompanyLevel> callback) {
		JsonObject json = new JsonObject();
		if (isCorrectAnswer(clevel, answer)) {
			json.addProperty("status", "Success");
			CompanyLevel nextLevel = clevel.getNextLevel();
			if (nextLevel != null)
				json.addProperty("key", nextLevel.getKey());
			callback.accept(nextLevel);
		} else {
			json.addProperty("status", "Incorrect Answer");
		}
		return json;
	}

	private static boolean isCorrectAnswer(CompanyLevel clevel, String answer) {
		answer = answer.replaceAll("[^A-Za-z]", "").toLowerCase();
		Pattern pattern = Pattern.compile(QuestionFactory.get(clevel).getAnswerPattern());
		return pattern.matcher(answer).matches();
	}
}
