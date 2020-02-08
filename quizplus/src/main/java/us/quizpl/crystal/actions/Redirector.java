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

@WebServlet(name = "CrystalRedirect", urlPatterns = { "/mpxp", "/wnej", "/nhyo", "/qaks", "/laje", "/sneo" })
public class Redirector extends HttpServlet {
	private static final long serialVersionUID = 5851426410344488046L;
	public static final String[] TEAM_PATHS = new String[] { "/mpxp", "/wnej", "/nhyo", "/qaks", "/laje", "/sneo" };

	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		doGet(req, resp);
	}

	public void doGet(HttpServletRequest req, HttpServletResponse response) throws IOException {
		int teamId = getTeamId(req.getRequestURI());
		response.sendRedirect("/win95/crui.html#/status/" + teamId);
	}

	private int getTeamId(String requestURI) {
		for (int i = 0; i < TEAM_PATHS.length; ++i)
			if (requestURI.contains(TEAM_PATHS[i]))
				return i + 1;
		return 0;
	}
}
