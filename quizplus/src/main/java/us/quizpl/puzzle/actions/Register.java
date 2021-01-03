package us.quizpl.puzzle.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;

import us.quizpl.puzzle.model.Person;

@WebServlet(name = "PuzzleRegister", urlPatterns = { "/api/rr/register" })
public class Register extends ActionBase {
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		String name = getText(request, PARAM_NAME);
		JsonObject json = Person.create(name).toJson();
		resp.setContentType("application/json");
		resp.getOutputStream().print(json.toString());
	}
}
