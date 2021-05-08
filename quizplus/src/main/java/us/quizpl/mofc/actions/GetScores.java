package us.quizpl.mofc.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;

import us.quizpl.halloween.model.LeaderBoardGenerator;

@WebServlet(name = "MofcGetScores", urlPatterns = { "/api/mofc/getscores" })
public class GetScores extends ActionBase {
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		JsonObject json = LeaderBoardGenerator.getAll();

		resp.setContentType("application/json");
		resp.getOutputStream().print(json.toString());
	}
}
