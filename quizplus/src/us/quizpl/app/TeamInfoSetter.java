package us.quizpl.app;

import java.io.IOException;
import javax.servlet.http.*;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import us.quizpl.app.model.TeamInfoAccessor;

@SuppressWarnings("serial")
public class TeamInfoSetter extends TeamInfoServletBase {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		TeamInfoAccessor accessor = getAccessor(req);
		String[] teamsAsJson = req.getParameterValues("team");
		if (teamsAsJson != null) {
			JsonParser parser = new JsonParser();
			for(String jsonTeamData : teamsAsJson) {
				JsonObject jsonObj  = parser.parse(jsonTeamData).getAsJsonObject();
				accessor.updateStateFromJson(jsonObj);
			}
		}
	}
}
