package us.quizpl.crystal.actions;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

import us.quizpl.crystal.model.TeamState;
import us.quizpl.crystal.model.TeamState.QuestionCategory;
import us.quizpl.crystal.model.TeamState.QuestionState;

@WebServlet(
	name = "CrystalGetState",
	urlPatterns = {"/cr/action/get"}
)
public class GetState extends HttpServlet {
	private static final long serialVersionUID = 5851426410344488046L;

	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		doGet(req, resp);
	}
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("application/json");
		JsonArray jsonObject = serializeTeamStates();
		resp.getOutputStream().print(jsonObject.toString());
	}
	private JsonArray serializeTeamStates() {
		JsonArray jsonArray = new JsonArray();
		for (int teamId = 1; teamId <= 6; ++teamId) {
			jsonArray.add(toJsonObject(TeamState.getOrCreate(teamId)));
		}
		return jsonArray;
	}
	private JsonObject toJsonObject(TeamState team) {
		JsonArray questionStates = new JsonArray();
		questionStates.add(toJsonObject(team.getQuestionState(QuestionCategory.PHYSICAL)));
		questionStates.add(toJsonObject(team.getQuestionState(QuestionCategory.MENTAL)));
		questionStates.add(toJsonObject(team.getQuestionState(QuestionCategory.MYSTERY)));
		questionStates.add(toJsonObject(team.getQuestionState(QuestionCategory.SKILL)));
		
		JsonObject teamJson = new JsonObject();
		teamJson.addProperty("id", team.getTeamId());
		teamJson.add("questions", questionStates);
		return teamJson;
	}
	private JsonObject toJsonObject(QuestionState questionState) {
		JsonObject questionJson = new JsonObject();
		questionJson.addProperty("answered", questionState.isAnswered);
		questionJson.addProperty("points", questionState.pointsAwarded);
		return questionJson;
	}
}
