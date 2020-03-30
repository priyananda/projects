package us.quizpl.online.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.online.model.AnswerAttempt;
import us.quizpl.online.model.Attempts;

@WebServlet(name = "OnlinePostAnswer", urlPatterns = { "/api/olq/postanswer" })
public class PostAnswer extends ActionBase {

	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long teamId = getLong(request, PARAM_TEAM);
		long questionId = getLong(request, PARAM_QUESTION);
		String name = getText(request, PARAM_NAME);
		String answerText = getText(request, PARAM_ANSWER);

		AnswerAttempt.create(teamId, questionId, name, answerText);
		
		resp.setContentType("application/json");
		resp.getOutputStream().print(Attempts.getAttemptsAsJson(teamId, questionId).toString());
	}
}
