package us.quizpl.mofc.model;

import java.util.function.Consumer;
import java.util.regex.Pattern;

import com.google.gson.JsonObject;

public class AnswerVerifier {
	public static JsonObject check(String key, String answer, Consumer<Void> callback) {
		JsonObject json = new JsonObject();
		if (isCorrectAnswer(key, answer)) {
			json.addProperty("status", "Success");
			callback.accept(null);
		} else {
			json.addProperty("status", "Incorrect Answer");
		}
		return json;
	}

	private static boolean isCorrectAnswer(String key, String answer) {
		answer = answer.replaceAll("[^A-Za-z0-9]", "").toLowerCase();
		Pattern pattern = Pattern.compile(QuestionFactory.get(key).getAnswerPattern());
		return pattern.matcher(answer).matches();
	}
}
