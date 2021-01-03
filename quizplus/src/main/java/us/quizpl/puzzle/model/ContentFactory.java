package us.quizpl.puzzle.model;

import com.google.gson.JsonObject;

import us.quizpl.puzzle.model.QuestionFactory.Question;

public class ContentFactory {
	public static JsonObject get(CompanyLevel companyLevel) {
		JsonObject json = new JsonObject();
		json.addProperty("company", companyLevel.getCompany().name());
		json.addProperty("level", companyLevel.getLevel());
		Question question = QuestionFactory.get(companyLevel);
		question.emitContent(json);
		if (shouldShowHint(companyLevel)) {
			json.addProperty("hint", question.getHint());
		}
		return json;
	}

	private static boolean shouldShowHint(CompanyLevel companyLevel) {
		return true;
	}
}
