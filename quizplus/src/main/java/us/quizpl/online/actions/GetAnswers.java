package us.quizpl.online.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.online.model.Attempts;

@WebServlet(name = "OnlineGetAnswers", urlPatterns = { "/api/olq/getanswers" })
public class GetAnswers extends ActionBase {
	
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long teamId = getLong(request, PARAM_TEAM);
		long questionId = getLong(request, PARAM_QUESTION);
		
		resp.setContentType("application/json");
		resp.getOutputStream().print(Attempts.getAttemptsAsJson(teamId, questionId).toString());
	}
}
