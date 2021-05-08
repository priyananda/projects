package us.quizpl.mofc.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;

import us.quizpl.mofc.model.AnswerSubmission;
import us.quizpl.mofc.model.AnswerVerifier;

@WebServlet(name = "MofcPostAnswer", urlPatterns = { "/api/mofc/postanswer" })
public class PostAnswer extends ActionBase {

	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long personId = getLong(request, PARAM_PERSON);
		String key = getText(request, PARAM_KEY);
		String answerText = getText(request, PARAM_ANSWER);

		JsonObject json = AnswerVerifier.check(key, answerText, newLevel -> {
			AnswerSubmission.create(personId, key);
		});

		resp.setContentType("application/json");
		resp.getOutputStream().print(json.toString());
	}
}
