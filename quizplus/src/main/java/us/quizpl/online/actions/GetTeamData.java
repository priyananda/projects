package us.quizpl.online.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.online.model.Team;

@WebServlet(name = "OnlineGetTeamData", urlPatterns = { "/api/olq/getteamdata" })
public class GetTeamData extends ActionBase {

	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long teamId = getLong(request, PARAM_TEAM);
		
		resp.setContentType("application/json");
		resp.getOutputStream().print(Team.getTeamData(teamId).toString());
	}
}
