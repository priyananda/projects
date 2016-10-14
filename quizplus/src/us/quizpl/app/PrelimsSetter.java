package us.quizpl.app;

import java.io.IOException;
import javax.servlet.http.*;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import us.quizpl.app.model.PrelimsState;

@SuppressWarnings("serial")
public class PrelimsSetter extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		String[] teamsAsJson = req.getParameterValues("team");
		if (teamsAsJson != null) {
			JsonParser parser = new JsonParser();
			for(String jsonTeamData : teamsAsJson) {
				JsonObject jsonObj  = parser.parse(jsonTeamData).getAsJsonObject();
				PrelimsState.updateStateFromJson(jsonObj);
			}
		}
	}
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		doGet(req, resp);
	}
}
