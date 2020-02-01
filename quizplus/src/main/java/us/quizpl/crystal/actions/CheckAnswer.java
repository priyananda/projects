package us.quizpl.crystal.actions;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.common.collect.ImmutableMap;
import com.google.gson.JsonObject;

import us.quizpl.crystal.model.TeamState;
import us.quizpl.crystal.model.TeamState.QuestionCategory;

@WebServlet(
	name = "CrystalCheckAnswer",
	urlPatterns = {"/cr/action/check"}
)
public class CheckAnswer extends HttpServlet {
	private static final long serialVersionUID = 5851426410344488046L;
	
	private static final ImmutableMap<QuestionCategory, String> ANSWERS = ImmutableMap.of(
		QuestionCategory.PHYSICAL, "foo",
		QuestionCategory.MENTAL, "doo",
		QuestionCategory.MYSTERY, "goo",
		QuestionCategory.SKILL, "zoo"
    );

	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		doGet(req, resp);
	}
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		resp.setContentType("application/json");
		JsonObject json = new JsonObject();
		if (validateAnswer(request)) {
			json.addProperty("result", Boolean.TRUE);
		}else {
			json.addProperty("result", Boolean.FALSE);
		}
		resp.getOutputStream().print(json.toString());
	}
	private boolean validateAnswer(HttpServletRequest request) {
		try {
			int teamId = Integer.parseInt(request.getParameter("team"));
			QuestionCategory question = QuestionCategory.valueOf(request.getParameter("q"));
			String answer = request.getParameter("a");
			
			if (teamId < 1 || teamId > 6 || answer == null || answer.isEmpty())
				return false;
			
			if (isCorrectAnswer(question, answer)) {
				TeamState team = TeamState.getOrCreate(teamId);
				team.answerQuestion(question, 10);
				team.save();
				return true;				
			}
			
			return false;
		} catch (Exception e) {
			return false;
		}
	}
	private boolean isCorrectAnswer(QuestionCategory question, String answer) {
		String correctAns = ANSWERS.get(question);
		String actualAns = answer.strip().toLowerCase();
		return correctAns.equals(actualAns);
	}
}
