package us.quizpl.puzzle.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;

import us.quizpl.online.model.Person;
import us.quizpl.puzzle.model.CompanyLevel;
import us.quizpl.puzzle.model.ContentFactory;

@WebServlet(name = "PuzzleGetContent", urlPatterns = { "/api/rr/getcontent" })
public class GetContent extends ActionBase {
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		String key = getText(request, PARAM_KEY);
		JsonObject json = ContentFactory.get(CompanyLevel.ofKey(key));

		resp.setContentType("application/json");
		resp.getOutputStream().print(json.toString());
	}
}
