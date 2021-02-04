package us.quizpl.jan21.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.jan21.model.Attempts;

@WebServlet(name = "Jan21GetAnswers", urlPatterns = { "/api/jan21/getanswers" })
public class GetAnswers extends ActionBase {
	
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long teamId = getLong(request, PARAM_TEAM);
		String questionSet = getText(request, PARAM_SET);
		long questionId = getLong(request, PARAM_QUESTION);
		
		resp.setContentType("application/json");
		resp.getOutputStream().print(Attempts.getAttemptsAsJson(teamId, questionSet, questionId).toString());
	}
}
