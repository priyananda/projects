package us.quizpl.puzzle.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;

import us.quizpl.online.model.Person;
import us.quizpl.puzzle.model.CompanyLevel;

@WebServlet(name = "PuzzleSwitch", urlPatterns = { "/api/rr/switch" })
public class Switch extends ActionBase {
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		String key = getText(request, PARAM_KEY);
		String newKey = CompanyLevel.ofKey(key).getPeerLevel().getKey();
		JsonObject json = new JsonObject();
		json.addProperty("key", newKey);
		resp.setContentType("application/json");
		resp.getOutputStream().print(json.toString());
	}
}
