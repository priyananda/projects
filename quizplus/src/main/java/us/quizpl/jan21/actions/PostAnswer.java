package us.quizpl.jan21.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.jan21.model.AnswerAttempt;
import us.quizpl.jan21.model.Attempts;

@WebServlet(name = "Jan21PostAnswer", urlPatterns = { "/api/jan21/postanswer" })
public class PostAnswer extends ActionBase {

	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long teamId = getLong(request, PARAM_TEAM);
		long questionId = getLong(request, PARAM_QUESTION);
		String name = getText(request, PARAM_NAME);
		String answerText = getText(request, PARAM_ANSWER);
		String questionSet = getText(request, PARAM_SET);

		AnswerAttempt.create(teamId, questionSet, questionId, name, answerText);
		
		resp.setContentType("application/json");
		resp.getOutputStream().print(Attempts.getAttemptsAsJson(teamId, questionSet, questionId).toString());
	}
}
